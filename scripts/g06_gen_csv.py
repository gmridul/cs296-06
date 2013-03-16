import subprocess
import os
import re

f=open('../data/lab05_g06_data.csv','w+')

for rerun in range(1,101):
    for iter in range(1,101):
        data=[]
        #out=subprocess.Popen(["../mybins/cs296_exe_06",str(iter)],stdout=subprocess.PIPE)
        out=subprocess.check_output(["../mybins/cs296_exe_06",str(iter)])
        out=out.decode("utf-8")

        data=re.findall('[\x30-\x39\x2E]+',out)
        f.write(str(rerun))

        for x in data:
            f.write(','+str(x))
        f.write('\n')

f.close()
