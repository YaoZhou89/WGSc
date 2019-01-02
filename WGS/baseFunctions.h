//
//  baseFunctions.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef baseFunctions_h
#define baseFunctions_h

#include <vector>

using namespace std;
typedef long int  lint ;

inline void  LogLackArg( string  flag )
{
    cerr << "\t\tLack Argument for [ -"<<flag<<" ]"<<endl;
}

/*
 inline string add_Asuffix ( string path )
 {
 string ext =path.substr(path.rfind('.') ==string::npos ? path.length() : path.rfind('.') + 1);
 if (ext != "gz")
 {
 path=path+".gz" ;
 }
 return path ;
 }
 */

inline string &  replace_all(string &  str,const  string &  old_Avalue,const string &  new_Avalue)
{
    while(true)   {
        string::size_type  pos(0);
        if(   (pos=str.find(old_Avalue))!=string::npos   )
            str.replace(pos,old_Avalue.length(),new_Avalue);
        else   break;
    }
    return   str;
}

inline void split(const string& str,vector<string>& tokens,  const string& delimiters = " ")
{
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}
inline bool depthTest(vector<double>  dep, const double  a, const double  b,double minDepth,double maxDepth, double depthSD){
    bool pass = false;
    double sum = 0.0, mean, standardDeviation = 0.0;
    int len = dep.size();
    for(int i = 0; i < len ; ++i){
        sum += dep[i];
    }
    if(sum < minDepth || sum > maxDepth){
        return false;
    }
    mean = sum/len;
    for(int i = 0; i < len ; ++i){
        standardDeviation += pow(dep[i] - mean, 2);
    }
    standardDeviation = sqrt(standardDeviation/(len-1));
    if(standardDeviation > depthSD | standardDeviation < 1.1){
        return false;
    }
//    cout << "sum is: " << sum << endl;
//    cout << "a is: " << a << endl;
//    cout << "b is: " << b << endl;
//    
    if((a + b*sum)>standardDeviation) pass = true;
    return pass;
}

inline double string2Double(std::string const& s){
        std::istringstream iss(s);
        double value;
        if (!(iss >> value)) throw std::runtime_error("invalid double");
        return value;
}

inline double string2Int(std::string const& s){
    std::istringstream iss(s);
    int value;
    if (!(iss >> value)) throw std::runtime_error("invalid int");
    return value;
}

#endif /* baseFunctions_h */
