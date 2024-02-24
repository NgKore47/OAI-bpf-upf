#!/bin/bash

# mkdir -p NF 
# Display current directory before and after cd
echo "Current directory: $(pwd)"
cd NFs

#git clone --recurse-submodules https://gitlab.eurecom.fr/oai/cn5g/oai-cn5g-upf.git -b develop 
cd oai-cn5g-upf
#git checkout ad060df53d4374c84845cfa1507cd8c24c099fbc
./build/scripts/build_upf -I -f -j -V
./build/scripts/build_upf -f -j -V
cd ..

#git clone --recurse-submodules https://gitlab.eurecom.fr/oai/cn5g/oai-cn5g-nrf.git -b develop
cd oai-cn5g-nrf
#git checkout 68dde4ed321208bf7d6cc8d18830cdd5ce31c6ef
./build/scripts/build_nrf -I -f -j -V
./build/scripts/build_nrf -f -j -V
cd ..

#git clone --recurse-submodules https://gitlab.eurecom.fr/oai/cn5g/oai-cn5g-amf.git -b develop
cd oai-cn5g-amf
#git checkout 2c31091d69682f8af6fac85320431c7bc41cbdd8
./build/scripts/build_amf -I -f -j -V
./build/scripts/build_amf -f -j -V
cd ..

#git clone --recurse-submodules https://gitlab.eurecom.fr/oai/cn5g/oai-cn5g-ausf.git -b develop
cd oai-cn5g-ausf
#git checkout d3d170dd5c821a93613a646395fda1609eea50f1
./build/scripts/build_ausf -I -f -j -V
./build/scripts/build_ausf -f -j -V
cd ..

#git clone --recurse-submodules https://gitlab.eurecom.fr/oai/cn5g/oai-cn5g-udm.git -b develop
cd oai-cn5g-udm
#git checkout 13a4cfd3c49df66488b6dea694fed297acf2d8ec
./build/scripts/build_udm -I -f -j -V
./build/scripts/build_udm -f -j -V
cd ..

#git clone --recurse-submodules https://gitlab.eurecom.fr/oai/cn5g/oai-cn5g-udr.git -b develop
cd oai-cn5g-udr
#git checkout 4c1efacf8ddf3a32d70af1d267ab8ddb93786eb6
./build/scripts/build_udr -I -f -j -V
./build/scripts/build_udr -f -j -V
cd ..

#git clone --recurse-submodules https://gitlab.eurecom.fr/oai/cn5g/oai-cn5g-smf.git -b develop
cd oai-cn5g-smf
#git checkout ffd50b6d9648ea37bdc75497a413a49eeeb29f99
./build/scripts/build_smf -I -f -j -V
./build/scripts/build_smf -f -j -V
cd ..


