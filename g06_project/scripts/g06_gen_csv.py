import subprocess
import os
import re

f=open('../data/g06_data.csv','w+')

for rerun in range(1,21):
    for iter in range(1,21):
        data=[]
        out=subprocess.check_output(["../bin/cs296_base_analysis",str(iter)])
        out=out.decode("utf-8")

        data=re.findall('[\x30-\x39\x2E]+',out)
        f.write(str(rerun))

        for x in data:
            f.write(','+str(x))
        f.write('\n')

f.close()
