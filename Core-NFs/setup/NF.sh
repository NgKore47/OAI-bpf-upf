#!/bin/bash

# Full names of NFs
NFS=("oai-cn5g-upf" "oai-cn5g-nrf" "oai-cn5g-amf" "oai-cn5g-ausf" "oai-cn5g-udm" "oai-cn5g-udr" "oai-cn5g-smf")

# Abbreviated names of NFs
NF=("upf" "nrf" "amf" "ausf" "udm" "udr" "smf")

# Display current directory before and after cd
cd NFs
echo "Initial directory: $(pwd)"

# Iterate over each NF in the array
for i in "${!NFS[@]}"; do
    cd ${NFS[$i]}
    echo "Current directory: $(pwd)"
    if ! command -v ${NF[$i]} &> /dev/null; then
        sleep 2
        echo "building deps for ${NF[$i]}" 
        ./build/scripts/build_${NF[$i]} -I -f -j -V
        sleep 1
        echo "installing ${NF[$i]}" 
        ./build/scripts/build_${NF[$i]} -f -j -V
    else
        echo "${NF[$i]} already present"
    fi   
    cd ..
done
