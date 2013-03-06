#!/bin/bash

# Fitzwilliam - Sudipto
# Darcy - Mridul
# Catherine - Sagar

cd data
rm -f pnp_austen_cs296.txt
touch pnp_austen_cs296.txt
 
sed '
s/``/"/g
s/'\'\''/"/g
s/Fitzwilliam/Sudipto/g
s/Darcy/Mridul/g
s/Catherine/Sagar/g ' <pnp_austen.txt >pnp_austen_cs296.txt
