#include "util.h"

#include <iostream>

Util::Util()
{
}

double Util::euclideanDistance(QVector2D from, QVector2D to)
{
    QVector2D delta = from - to;
    return sqrt(pow(delta.x(), 2) + pow(delta.y(), 2));
}

std::vector<QVector2D> Util::bresenham(QVector2D p1, QVector2D p2)
{
    int dx = p2.x() - p1.x(), dy = p2.y() - p1.y()
       , dx1 = abs(dx), dy1 = abs(dy)
       , px = 2*dy1-dx1, py = 2*dx1-dy1
       , x, y, xe, ye;
    std::vector<QVector2D> r;
    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = p1.x();
            y = p1.y();
            xe = p2.x();
        } else {
            x = p2.x();
            y = p2.y();
            xe = p1.x();
        }
        r.push_back(QVector2D(x, y));
        for (int i = 0; x < xe; i++) {
            x++;
            if (px < 0) px += 2*dy1;
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y++;
                else y--;
                px += 2*(dy1-dx1);
            }
            r.push_back(QVector2D(x, y));
        }
    } else {
        if (dy >= 0) {
            x = p1.x();
            y = p1.y();
            ye = p2.y();
        } else {
            x = p2.x();
            y = p2.y();
            ye = p1.y();
        }
        r.push_back(QVector2D(x, y));
        for (int i = 0; y < ye; i++) {
            y++;
            if (py <= 0) py += 2*dx1;
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x++;
                else x--;
                py += 2*(dx1-dy1);
            }
            r.push_back(QVector2D(x, y));
        }
    }
    return r;
}

std::vector<QVector2D> Util::dubins(State qn, State qr, double step)
{
    std::vector<State> rs;
    std::vector<QVector2D> r;
    std::vector<QVector2D> e;
    double dubinsR = 0.1;
    State centerA, centerB;
    double phi = 0.2;

    double tan_vitual = tan(qn.th()+M_PI/4);
    double x_no_sign_squre =pow(dubinsR,2)/(1+(pow(tan_vitual,2)));
    double x_no_sign =sqrt(x_no_sign_squre);
    double xc_a_1 = qn.x()+x_no_sign;
    double xc_a_2 = qn.x()-x_no_sign;
    double yc_a_1 = x_no_sign*tan_vitual+qn.y();
    double yc_a_2 = (-x_no_sign)*tan_vitual+qn.y();
    State center1(xc_a_1,yc_a_1,0);
    State center2(xc_a_2,yc_a_2,0);

    double distCenterPoint1 = Util::euclideanDistance(center1,qr);
    double distCenterPoint2 = Util::euclideanDistance(center2,qr);

    //centerA = distCenterPoint1<distCenterPoint2?center1:center2;
    if(distCenterPoint1<distCenterPoint2)
        centerA=center1;
    else
        centerA=center2;

    double thetaCenter = atan2(qn.y()-centerA.y(), qn.x()-centerA.x());
    //test111
    double tmpDeltaTheta = qn.th() - thetaCenter;
    if (tmpDeltaTheta>M_PI) {
        tmpDeltaTheta -= 2*M_PI;
    }

    //cout<<endl<<"thetaCenter angle: "<< thetaCenter<<" qn.theta: "<< qn.theta <<"==> \n------------------- theta-center.theta for A:"<<tmpDeltaTheta<<endl;

    if(floor(tmpDeltaTheta*1000) == floor((M_PI/4)*1000)){
        centerA.setTh(1);//anti-clockwise
    }else{
        centerA.setTh(-1);//clockwise
    }
    //cout<<"centerA.theta "<<qn.theta/PI*180<<":"<<centerA.theta<<endl;

    //Point B
    tan_vitual=tan(qr.th()+M_PI/4);
    x_no_sign_squre =pow(dubinsR,2)/(1+(pow(tan_vitual,2)));
    x_no_sign =sqrt(x_no_sign_squre);
    double xc_b_1 = qr.x()+x_no_sign;
    double xc_b_2 = qr.x()-x_no_sign;
    double yc_b_1 = x_no_sign*tan_vitual+qr.y();
    double yc_b_2 = (-x_no_sign)*tan_vitual+qr.y();
    State center3(xc_b_1,yc_b_1,0);
    State center4(xc_b_2,yc_b_2,0);
    //cout<<"center1: ";center1.coutPoint();//
    //cout<<"center2: ";center2.coutPoint();//
    distCenterPoint1 = Util::euclideanDistance(center3,qn);
    distCenterPoint2 = Util::euclideanDistance(center4,qn);
    //centerB = distCenterPoint1<distCenterPoint2?center1:center2;
    if(distCenterPoint1<distCenterPoint2)
        centerB=center3;
    else
        centerB=center4;

    thetaCenter = atan2(qr.y()-centerB.y(), qr.x()-centerB.x());

    //test111
    tmpDeltaTheta = qr.th() - thetaCenter;
    if (tmpDeltaTheta>M_PI) {
        tmpDeltaTheta -= 2*M_PI;
    }
    //cout<<endl<<"thetaCenter angle: "<<thetaCenter<<" qr.theta: "<<qr.theta<<" ==>"<<"\n----------------- theta-center.theta for B: "<<tmpDeltaTheta<<endl;
    if(floor(tmpDeltaTheta*1000) == floor((M_PI/4)*1000)){
        centerB.setTh(1);//anti-clockwise
    }else{
        centerB.setTh(-1);//clockwise
    }
    //cout<<"centerB.theta "<<qr.theta/PI*180<<":"<<centerB.theta<<endl;
    //finish initial B

    // calculate the angle theta, distance of segment(centerA, centerB)
    double tmpAngleCenters = atan2(centerB.y()-centerA.y(), centerB.x()-centerA.x());
    //cout<<"tmpAngleCenters: "<<tmpAngleCenters<<endl;
    double angleCenters = tmpAngleCenters > 0? tmpAngleCenters : 2*M_PI+tmpAngleCenters;//adjust the range from [-PI,PI] to [0,2PI]
    double distCenters = Util::euclideanDistance(centerA,centerB);
    //cout<<"distA->B "<<distCenters<<endl;
    //if the distance between two centers is too small, then the curve doesn't exist, break out.
    if(distCenters<2*dubinsR)
        return e;

    //push the first point into the vector
    State new_point(round(qn.x()),round(qn.y()),qn.th());

    rs.push_back(new_point);
    r.push_back(QVector2D(new_point.x(), new_point.y()));

    //-------------------------this is the begin of moving--------------------------//
    if(floor(centerA.th()*1000) == floor(centerB.th()*1000)){

        //same circle direction strategy: tangent line not seperate 2 circles, circles on the same side of line
        // the whole motion path composed of turning C1, going streight S, turning C2.
        // path of turning C1
        //keep turning until (A.theta == angleCenters), then leave this circle
        //make sure A.theta will wrap up at 0-2PI range.
        // angle step size is phi*directionOfCircle

        double tempAthetaC1 = qn.th()*centerA.th();
        //cout<<"angleCenters: "<<angleCenters<<endl;
        double angleLeave = angleCenters*centerA.th();
        if(tempAthetaC1 > angleLeave){//handle case: tempAthetaC1 > angleLeave
            angleLeave += 2*M_PI;
        }

        while(true){
            //cout<<"tempAthetaC1: "<<tempAthetaC1<<" angleLeave: "<<angleLeave<<" phi: "<<phi<<endl;
            if( tempAthetaC1 + phi > angleLeave){
                State tmpp = Util::dubinsTurn(rs.back(), (angleLeave-tempAthetaC1)*centerA.th(), centerA);// turn A to angle angleCenters arond centerA, last move, ready to leave
                if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
                //cout<<"obstacle, and NULL"<<endl;
                    return e;
                }
                //tmpp->coutPoint();
                rs.push_back(tmpp);
                r.push_back(QVector2D(tmpp.x(), tmpp.y()));
                break;
            }
            State tmpp = Util::dubinsTurn(rs.back(), phi*centerA.th(), centerA);// turn A phi angle around centerA
            if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
                //cout<<"obstacle, and NULL"<<endl;
                return e;
            }
            //tmpp->coutPoint();
            rs.push_back(tmpp);
            r.push_back(QVector2D(tmpp.x(), tmpp.y()));
            // update tempAthetaC1
            tempAthetaC1 = tempAthetaC1+phi;
        }
        //cout<<endl<<"leaving C1 at : ";
        //nextTurnP.back()->coutPoint();
        // path of going streight S
        // keep going streight for distance of distCenters,
        // then it reach the tangent point from streight line to circle B.
        double currentDist=0;
        while(true){
            // move Point A one stepSizeStreight forward
            if(currentDist+step > distCenters){
                std::vector<State> tmpp = Util::dubinsFoward(rs.back(), distCenters-currentDist); // last move
                if (tmpp.size() == 0) {// collision happen, stop curve and return dubins()
    //                    cout<<"obstacle, and NULL"<<endl;
                    return e;
                }
                for (int i = 0; i < tmpp.size(); i++) {
                    rs.push_back(tmpp[i]);
                    r.push_back(QVector2D(tmpp[i].x(), tmpp[i].y()));
                }
                break;
            }
            std::vector<State> tmpp = Util::dubinsFoward(rs.back(), step);// normal move
            if (tmpp.size() == 0) {// collision happen, stop curve and return dubins()
//                    cout<<"obstacle, and NULL"<<endl;
                return e;
            }
            for (int i = 0; i < tmpp.size(); i++) {
                rs.push_back(tmpp[i]);
                r.push_back(QVector2D(tmpp[i].x(), tmpp[i].y()));
            }
            //update currentDist
            currentDist +=step;
        }


        // path of turing C2
        //keep turning until (A.theta == B.theta), then path done, reach destination
        //make sure A.theta will wrap up at 0-2PI range.
        // angle step size is phi*directionOfCircle
        double tempAthetaC2 = rs.back().th()*centerB.th();
        double angleDone = qr.th()*centerB.th();
        if(tempAthetaC2 > angleDone){//handle case: tempAthetaC2 > angleDone
            angleDone += 2*M_PI;
        }
        while(true){
            if( tempAthetaC2 + phi > angleDone){
                State tmpp = Util::dubinsTurn(rs.back(), (angleDone-tempAthetaC2)*centerB.th(), centerB);// turn A to angle angleCenters around centerB, last move, path done
                if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
                    //cout<<"obstacle, and NULL"<<endl;
                    return e;
                }
                //                    tmpp->coutPoint();
                rs.push_back(tmpp);
                r.push_back(QVector2D(tmpp.x(), tmpp.y()));
                break;
            }
            State tmpp = Util::dubinsTurn(rs.back(), phi*centerB.th(),centerB);// turn A phi angle around centerB
            if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
//                    cout<<"obstacle, and NULL"<<endl;
                return e;
            }
            // update tempAthetaC2
            rs.push_back(tmpp);
            r.push_back(QVector2D(tmpp.x(), tmpp.y()));
            //                tmpp->coutPoint();
            tempAthetaC2 = tempAthetaC2+phi;
        }
    }//end of dubins curve for same circle direction case
    else{
        // the whole motion path composed of turning C1, going streight S, turning C2.
        // path of turning C1
        //keep turning until (A.theta == angleTangentLine), then leave this first circle
        double absAngleCenterLine2TangentLine = asin((double)dubinsR/(distCenters/2));// abs(angle from centerLine to tangentLine)
        double angleTangentLine = angleCenters + absAngleCenterLine2TangentLine*centerA.th();
        //make sure A.theta will wrap up at 0-2PI range.
        // angle step size is phi*directionOfCircle
        double tempAthetaC1 = qn.th()*centerA.th();
        double angleLeave = angleTangentLine*centerA.th();
        if(tempAthetaC1 > angleLeave){//handle case: tempAthetaC1 > angleLeave
            angleLeave += 2*M_PI;
        }
        while(true){
            if( tempAthetaC1 + phi > angleLeave){
                State tmpp=Util::dubinsTurn(rs.back(), (angleLeave-tempAthetaC1)*centerA.th(), centerA);// turn A to angle angleCenters around centerA, last move, ready to leave
                if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
//                        cout<<"obstacle, and NULL"<<endl;
                    return e;
                }
                rs.push_back(tmpp);
                r.push_back(QVector2D(tmpp.x(), tmpp.y()));
                //                    tmpp->coutPoint();
                break;
            }
            State tmpp =Util::dubinsTurn(rs.back(), phi*centerA.th(), centerA);// turn phi angle around centerA
            if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
//                    cout<<"obstacle, and NULL"<<endl;
                return e;
            }
            // update tempAthetaC1
            rs.push_back(tmpp);
            r.push_back(QVector2D(tmpp.x(), tmpp.y()));
            //                tmpp->coutPoint();
            tempAthetaC1 = tempAthetaC1+phi;
        }
        // path of going streight S
        // keep going streight for distance of distTangentLine,
        // 	then it reach the tangent point from streight line to circle B.
        double distTangentLine = 2*sqrt(pow(distCenters/2,2)-pow(dubinsR,2));
        double currentDist = 0;// record the current distance on the streight line
        while(true){
            // move Point A one stepSizeStreight forward
            if(currentDist+step > distTangentLine){
                std::vector<State> tmpp=Util::dubinsFoward(rs.back(), distTangentLine-currentDist); // last move
                if (tmpp.size() == 0) {// collision happen, stop curve and return dubins()
    //                    cout<<"obstacle, and NULL"<<endl;
                    return e;
                }
                for (int i = 0; i < tmpp.size(); i++) {
                    rs.push_back(tmpp[i]);
                    r.push_back(QVector2D(tmpp[i].x(), tmpp[i].y()));
                }
                break;
            }
            std::vector<State> tmpp=Util::dubinsFoward(rs.back(), step);// normal move
            if (tmpp.size() == 0) {// collision happen, stop curve and return dubins()
//                    cout<<"obstacle, and NULL"<<endl;
                return e;
            }
            for (int i = 0; i < tmpp.size(); i++) {
                rs.push_back(tmpp[i]);
                r.push_back(QVector2D(tmpp[i].x(), tmpp[i].y()));
            }
            currentDist += step;
        }

        // path of turing C2
        //keep turning until (A.theta == B.theta), then path done, reach destination
        //make sure A.theta will wrap up at 0-2PI range.
        // angle step size is phi*directionOfCircle
        double tempAthetaC2 = rs.back().th()*centerB.th();
        double angleDone = qr.th()*centerB.th();
        if(tempAthetaC2 > angleDone){//handle case: tempAthetaC2 > angleDone
            angleDone += 2*M_PI;
        }
        while(true){
            if( tempAthetaC2 + phi > angleDone){
                State tmpp=Util::dubinsTurn(rs.back(), (angleDone-tempAthetaC2)*centerB.th(), centerB);// turn A to angle angleCenters around centerB, last move, path done
                if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
//                        cout<<"obstacle, and NULL"<<endl;
                    return e;
                }
                //                    tmpp->coutPoint();
                rs.push_back(tmpp);
                r.push_back(QVector2D(tmpp.x(), tmpp.y()));
                break;
            }
            State tmpp=Util::dubinsTurn(rs.back(), phi*centerB.th(), centerB);// turn A phi angle around centerB
            if (tmpp.isNull()) {// collision happen, stop curve and return dubins()
//                    cout<<"obstacle, and NULL"<<endl;
                return e;
            }
            // update tempAthetaC2
            //                tmpp->coutPoint();
            rs.push_back(tmpp);
            r.push_back(QVector2D(tmpp.x(), tmpp.y()));
            tempAthetaC2 = tempAthetaC2+phi;
        }
    }//end of dubins curve for diff circle direction case

    rs.push_back(qr);
    r.push_back(QVector2D(qr.x(), qr.y()));

    return r;
}

State Util::dubinsTurn(State p1, double deltaAngle, State center)
{
    //update position and orientation
    double tmpNewTheta = p1.th() + deltaAngle;
    double newTheta;
    double dubinsR = 1.3;
    if (tmpNewTheta >= 2*M_PI) {// adjust the range of new theta into [0,2PI)
        newTheta = tmpNewTheta - 2*M_PI;
    }else if(tmpNewTheta < 0){
        newTheta = tmpNewTheta + 2*M_PI;
    }else{
        newTheta = tmpNewTheta;
    }
    //        cout<<"newTheta: "<<newTheta<<endl;//
    double deltaX2center = dubinsR*cos(newTheta-center.th()*M_PI/4);
    double deltaY2center = dubinsR*sin(newTheta-center.th()*M_PI/4);
    double newX = center.x() + deltaX2center;
    double newY = center.y() + deltaY2center;
    //create Point at new position and orientation
    State newP(round(newX), round(newY), newTheta);
    return newP;
}

std::vector<State> Util::dubinsFoward(State A, double distance)
{
    //update postion
    std::vector<State> r;
    double newX = A.x() + distance*cos(A.th());
    double newY = A.y() + distance*sin(A.th());
    State newP(round(newX), round(newY), A.th());

    std::vector<QVector2D> d = Util::bresenham(A, newP);

    for (int i = 0; i < d.size(); i++) {
        r.push_back(State(round(d[i].x()), round(d[i].y()), A.th()));
    }

    return r;
}
