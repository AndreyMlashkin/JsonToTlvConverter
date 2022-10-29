# json_tlv_converter_nxlog
This application should take a simplified JSON file as input and output the information to a TLV format.

## Getting started
in order to get this project running, you will need git, working c++ compiler, cmake and conan.

In order to run the project and tests, you may need these commands (it should work on any system, including windows):

git clone https://gitlab.com/malashkin.andrey/json_tlv_converter_nxlog.git
git submodule update --init
pip install conan -y
cd json_tlv_converter_nxlog
conan create . --build missing
 

## Project status
In development
