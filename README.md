# json_tlv_converter_nxlog
This application should take a simplified JSON file as input and output the information to a TLV format.

## Getting started
in order to get this project running, you will need git, working c++ compiler, cmake and conan.

In order to run the project and tests, you may need these commands (it should work on any system, including windows):

```
git clone https://gitlab.com/malashkin.andrey/json_tlv_converter_nxlog.git
git submodule update --init
pip install conan -y
cd json_tlv_converter_nxlog
conan create . --build missing
```

## Project dependencies
Project uses Nativejson for parsing because it has the best performance comparing to other libs:
https://github.com/miloyip/nativejson-benchmark

Project uses Jhuster/TLV for writing because there are very few alternatives and this one has the biggest rating on github
https://github.com/Jhuster/TLV

However, during implementation and testing, I submitted isses and pull requests there:
https://github.com/Jhuster/TLV/pull/12
https://github.com/Jhuster/TLV/issues/11

## Project status
Done
