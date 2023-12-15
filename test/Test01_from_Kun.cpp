//This is a test file which can have a check on installing of OpenVINO
#include<openvino/openvino.hpp>
#include<iostream>

using namespace std;

 int main(){

    ov::Core core;
    vector<string> avilableDevice = core.get_available_devices();
    for(auto x:avilableDevice)
    {
        cout<<"avilableDevice:::"<<x<<endl;
        cout<<"momomomomomo"<<endl;
    
    }

    
}

