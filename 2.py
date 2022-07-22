# EXP 2 - Scalability: Obtain distance for a fixed scale  //
# @file 2.py
# @author Unai Alro
# @version 07/12/21

# This program produces the figures for the results of 2.cpp program.

import numpy as np
import matplotlib
import matplotlib.pyplot as plt

# save
save0=1

# paths
pth0="/home/unai/Documents/wk/rxv/kronos/sim/4/"
pth1="2/"

pth=pth0+pth1

# read
datin=open(pth+"M.txt",'r')
datM=[[int(i1) for i1 in i0.split()] for i0 in datin.readlines()];
datin.close()

# labels
label0=[r"$|X_i|="+str(datM[0][0]+e0*datM[0][2])+"$" for e0 in range(datM[0][3])]
label1=[r"$N="+str(datM[1][0]+e1*datM[1][2])+"$" for e1 in range(datM[1][3])]

# plotstyle
FS=20;plt.rc('xtick', labelsize=FS);plt.rc('ytick', labelsize=FS)
plt.rcParams.update({'font.size': FS})

lins=['-','--','-.',':']
markers=['1','2','3','4']
colors=[(0,0.75,0.25),(0,0.5,0.5),(0,0.25,0.75)]

# f0
f0,ax0=plt.subplots()
for i0 in range(datM[0][3]):
    pth2=str(datM[0][0]+datM[0][2]*i0)

    datin=open(pth0+pth1+"sm"+pth2+".txt",'r')
    sm=[[float(i1) for i1 in i0.split()] for i0 in datin.readlines()]
    datin.close()
 
    for i1 in range(datM[1][3]):
        tplot=[i2 for i2 in sm[i1] if i2!=0]
        ax0.plot(tplot,marker=markers[i1],color=colors[i0],linestyle=lins[i1],lw=1,markersize=10)

lines=ax0.get_lines()
legend0=plt.legend([lines[datM[1][3]*i0] for i0 in [i1 for i1 in range(datM[0][3])]], label0, loc=1)
legend1=plt.legend([lines[i0] for i0 in range(datM[1][3])],label1, loc=2)
ax0.add_artist(legend0)
ax0.add_artist(legend1)

ax0.set_ylabel(r'$\sigma(T,\hat{T})$');ax0.set_ylim([0,0.025])
ax0.set_xlabel(r'$o$');ax0.set_xticks([i0 for i0 in range(datM[2][3])]);ax0.set_xticklabels([i0+2 for i0 in range(datM[2][3])])

# f1
f1,ax1=plt.subplots()
for i0 in range(datM[0][3]):
    pth2=str(datM[0][0]+datM[0][2]*i0)

    datin=open(pth+"si"+pth2+".txt",'r')
    si=[[float(i1) for i1 in i0.split()] for i0 in datin.readlines()]
    datin.close()

    for i1 in range(datM[1][3]):
        tplot=[i2 for i2 in si[i1] if i2!=0]
        ax1.plot(tplot,marker=markers[i1],color=colors[i0],linestyle=lins[i1],lw=1,markersize=10)


lines=ax1.get_lines()
legend0=plt.legend([lines[datM[1][3]*i0] for i0 in [i1 for i1 in range(datM[0][3])]], label0, loc=1)
legend1=plt.legend([lines[i0] for i0 in range(datM[1][3])],label1, loc=2,framealpha=0.5)
ax1.add_artist(legend0)
ax1.add_artist(legend1)

ax1.set_ylabel(r'$\sigma(\mathbf{a},\hat{\mathbf{a}})$');ax1.set_ylim([0,0.2])
ax1.set_xlabel(r'$o$');ax1.set_xticks([i0 for i0 in range(datM[2][3])]);ax1.set_xticklabels([i0+2 for i0 in range(datM[2][3])])

# f2
f2,ax2=plt.subplots()
for i0 in range(datM[0][3]):
    pth2=str(datM[0][0]+datM[0][2]*i0)

    datin=open(pth0+pth1+"sr"+pth2+".txt",'r')
    sr=[[float(i1) for i1 in i0.split()] for i0 in datin.readlines()]
    datin.close()

    for i1 in range(datM[1][3]):
        rplot=[i2 for i2 in sr[i1] if i2!=0]
        ax2.plot(rplot,marker=markers[i1],color=colors[i0],linestyle=lins[i1],lw=1,markersize=10)

lines=ax2.get_lines()
legend0=plt.legend([lines[datM[1][3]*i0] for i0 in [i1 for i1 in range(datM[0][3])]],label0, loc=1,fancybox=True,framealpha=0.5)
legend1=plt.legend([lines[i0] for i0 in range(datM[1][3])],label1, loc=2,fancybox=True,framealpha=0.5)
ax2.add_artist(legend0)
ax2.add_artist(legend1)

ax2.set_ylabel(r'$|r-\hat{r}|$');ax2.set_ylim([0,0.025])
ax2.set_xlabel(r'$o$');ax2.set_xticks([i0 for i0 in range(datM[2][3])]);ax2.set_xticklabels([i0+2 for i0 in range(datM[2][3])])

# show
plt.show()

# save
if save0:
    f0.savefig(pth+"fig/2"+"sm"+".pdf",bbox_inches='tight',dpi=300)
    f1.savefig(pth+"fig/2"+"si"+".pdf",bbox_inches='tight',dpi=300)
    f2.savefig(pth+"fig/2"+"sr"+".pdf",bbox_inches='tight',dpi=300)

