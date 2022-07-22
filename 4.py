# EXP 4 - Musical notes  //
# @file 4.py
# @author Unai Alro
# @version 08/12/21

# This program produces the figures for the results of 4.cpp program.

import math
import numpy as np
import matplotlib
import matplotlib.pyplot as plt

# save
save0=1

# paths
pth0="/home/unai/Documents/wk/rxv/kronos/sim/4/"
pth1="4/"
pth=pth0+pth1

# read
f0=open(pth+"ecoeffs.txt",'r')
ecoeffs=[float(val) for line in f0.readlines() for val in line.split()]
f0.close()
logEcoeffs=[math.log(i0,2) for i0 in ecoeffs]

f0=open(pth+"eorders.txt",'r')
eorders=[int(val) for line in f0.readlines() for val in line.split()]
f0.close()

f0=open(pth+'etypes.txt','r')
etypess=[''.join([val for val in line.split()]) for line in f0.readlines()]
f0.close()

f0=open(pth+'etypes.txt','r')
etypesi=[[int(val) for val in line.split()] for line in f0.readlines()]
f0.close()

f0=open(pth+'distribution.txt','r')
distribution=[[float(val) for val in line.split()] for line in f0.readlines()]
f0.close()

f0=open(pth+'cdistribution.txt','r')
cdistribution=[[float(val) for val in line.split()] for line in f0.readlines()]
f0.close()

# plotstyle
FS=20;plt.rc('xtick', labelsize=FS);plt.rc('ytick', labelsize=FS)
plt.rcParams.update({'font.size': FS})

# preparation
N=len(etypesi[0])
dx=[0.1 for i0 in ecoeffs]; dx[4]=-0.25
dy=[-0.075 for i0 in ecoeffs]

angles=[i0*2*np.pi/N for i0 in range(N)]

# f0
f0,ax0=plt.subplots()
ax0.scatter(eorders,logEcoeffs,color=[(0,0,0) for i0 in ecoeffs])
for i0, txt in enumerate(etypess):
    ax0.annotate(txt,(eorders[i0]+dx[i0],logEcoeffs[i0]+dy[i0]),fontsize=10)
ax0.set_xlabel(r'$\omega$')
ax0.set_ylabel(r'$\log_2 a$')

# f1
f1,ax1=plt.subplots()
ax1.plot(distribution[0],distribution[1],label=r"$k$",linestyle='-',marker='.',color='k')
ax1.plot(cdistribution[0],cdistribution[1],label=r"$k^c$",linestyle='--',color='k')
ax1.fill_between(cdistribution[0],cdistribution[1],color=(0.5,0.5,0.5,0.5))
ax1.set_xlabel(r"$l$")
ax1.set_xticks([0,0.5,1])
ax1.set_xticklabels([0,r"$\frac{1}{2}\lambda_{MC}$",r"$\lambda_{MC}$"])
ax1.legend(prop={'size':15})

#f2
f2 = plt.figure()
ax2=f2.add_subplot(111,polar=True)
for i0 in range(len(etypesi)-1):
    radius=[i1+i0*0 for i1 in etypesi[i0]]
    radius+=[radius[0]]
    ax2.plot(angles+[0],radius,alpha=ecoeffs[i0])
    ax2.fill(angles+[0],radius,alpha=0.5*ecoeffs[i0])
for i0 in range(len(etypesi)-1,len(etypesi)):
    radius=[i1+i0*0 for i1 in etypesi[i0]]
    radius+=[radius[0]]
    ax2.plot(angles+[0],radius,alpha=ecoeffs[i0],color=(0,0.5,1))
    ax2.fill(angles+[0],radius,alpha=0.5*ecoeffs[i0],color=(0,0.5,1))

plt.xticks(angles,[r"$s_"+str(i0)+"$" for i0 in range(N)])
plt.xticks(angles,["tonic","third","fifth"])
plt.yticks([0,1,2,3,4,5],["",r"$t$",r"$t-1$",r"$t-2$",r"$t-3$",r"$t-4$"],fontsize=15)
ax2.spines['polar'].set_visible(False)
plt.show()

# show
plt.show()

# save
if save0:
    f0.savefig(pth+"fig/4"+"a"+".pdf",bbox_inches='tight',dpi=300)
    f1.savefig(pth+"fig/4"+"w"+".pdf",bbox_inches='tight',dpi=300)
    f2.savefig(pth+"fig/4"+"i"+".pdf",bbox_inches='tight',dpi=300)

