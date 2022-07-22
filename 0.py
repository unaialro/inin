# EXP 0 - Scalability: Obtain distance for different lengths  //
# @file 0.py
# @author Unai Alro
# @version 06/12/21

# This program produces the figures for the results of 0.cpp program.

import numpy as np
import matplotlib
import matplotlib.pyplot as plt

# save
save0=1

# paths
X=2
O=3

pth0="/home/unai/Documents/wk/rxv/kronos/sim/4/"
pth1="0/"
pth2=str(X)+"/"
pth3=str(O)+"/"

pth=pth0+pth1+pth2+pth3

# read
datin=open(pth+"M.txt",'r')
M=[[float(i1) for i1 in i0.split() if i1!=0] for i0 in datin.readlines()]
datin.close()

for i0 in range(len(M)-1):
    for i1 in range(4):
        if i1!=2:
            M[i0][i1]=int(M[i0][i1])

for i0 in range(len(M[-1])):
    M[-1][i0]=int(M[-1][i0])        

datin=open(pth+"sm.txt",'r')
sm=[[float(i1) for i1 in i0.split() if i1!=0] for i0 in datin.readlines()]
datin.close()

datin=open(pth+"si.txt",'r')
si=[[float(i1) for i1 in i0.split() if i1!=0] for i0 in datin.readlines()]
datin.close()

datin=open(pth+"sr.txt",'r')
sr=[[float(i1) for i1 in i0.split() if i1!=0] for i0 in datin.readlines()]
datin.close()

# labels
label0=[r"$N="+str(int(M[0][0]+e0*M[0][2]))+"$" for e0 in range(M[0][3])]

# plotstyle
FS=25;plt.rc('xtick', labelsize=FS);plt.rc('ytick', labelsize=FS)
plt.rcParams.update({'font.size': FS})

colors=[(0,0.75,0.25),(0,0.5,0.5),(0,0.25,0.75),(0,0,1)]

'''
#f0
f0,ax0=plt.subplots()
for i0 in range(len(sm)):
    ax0.plot(sm[i0],color=colors[i0],lw=1)
ax0.set_ylim([0,0.15])

lines=ax0.get_lines()
legend0=plt.legend([lines[i0] for i0 in range(M[0][3])],label0,loc=1,framealpha=0.5)
ax0.add_artist(legend0)

ax0.set_xlabel(r"$\eta$")
ax0.set_xticks([i0/0.5 for i0 in range(4)])
ax0.set_xticklabels([r"$10^"+str(i0+1)+"$" for i0 in range(4)])
ax0.set_ylabel(r"$\sigma(T,\hat{T})$")

#f1
f1,ax1=plt.subplots()
for i0 in range(len(sm)):
    ax1.plot(si[i0],color=colors[i0],lw=1)
ax1.set_ylim([0,0.5])

lines=ax1.get_lines()
legend0=plt.legend([lines[i0] for i0 in range(M[0][3])],label0,loc=1,framealpha=0.5)
ax1.add_artist(legend0)

ax1.set_xlabel(r"$\eta$")
ax1.set_xticks([i0/0.5 for i0 in range(4)])
ax1.set_xticklabels([r"$10^"+str(i0+1)+"$" for i0 in range(4)])
ax1.set_ylabel(r"$\sigma(\mathbf{a},\hat{\mathbf{a}})$")

#f2
f2,ax2=plt.subplots()
for i0 in range(len(sm)):
    ax2.plot(sr[i0],color=colors[i0],lw=1)
ax2.set_ylim([0,0.15])

lines=ax2.get_lines()
legend0=plt.legend([lines[i0] for i0 in range(M[0][3])],label0,loc=1,framealpha=0.5)
ax2.add_artist(legend0)

ax2.set_xlabel(r"$\eta$")
ax2.set_xticks([i0/0.5 for i0 in range(4)])
ax2.set_xticklabels([r"$10^"+str(i0+1)+"$" for i0 in range(4)])
ax2.set_ylabel(r"$|r-\hat{r}|$")

# show
plt.show()

# save
if save0:
    f0.savefig(pth+'fig/0'+"sm"+str(O)+".pdf",bbox_inches='tight',dpi=300)
    f1.savefig(pth+'fig/0'+"si"+str(O)+".pdf",bbox_inches='tight',dpi=300)
    f2.savefig(pth+'fig/0'+"sr"+str(O)+".pdf",bbox_inches='tight',dpi=300)
'''

#f0
f0,ax0=plt.subplots()
for i0 in range(len(sm)):
    ax0.plot(sm[i0],si[i0],color=colors[i0],lw=1)

lines=ax0.get_lines()
legend0=plt.legend([lines[i0] for i0 in range(M[0][3])],label0,loc=4,framealpha=0.5)
ax0.add_artist(legend0)

ax0.set_xticks([0,0.05,0.10])
ax0.set_xlabel(r"$\sigma(T,\hat{T})$")  
ax0.set_ylabel(r"$\sigma(\mathbf{a},\hat{\mathbf{a}})$")

#f1
f1,ax1=plt.subplots()
for i0 in range(len(sm)):
    ax1.plot(sm[i0],sr[i0],color=colors[i0],lw=1)

lines=ax1.get_lines()
legend0=plt.legend([lines[i0] for i0 in range(M[0][3])],label0,loc=2,framealpha=0.5)
ax1.add_artist(legend0)

ax1.set_xticks([0,0.05,0.10])
ax1.set_yticks([0,0.05,0.10])
ax1.set_xlabel(r"$\sigma(T,\hat{T})$")  
ax1.set_ylabel(r"$|r-\hat{r}|$")

plt.show()

#save
if save0:
    f0.savefig(pth+'fig/0'+"mi"+str(O)+".pdf",bbox_inches='tight',dpi=300)
    f1.savefig(pth+'fig/0'+"mr"+str(O)+".pdf",bbox_inches='tight',dpi=300)




