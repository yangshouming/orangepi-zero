#!/usr/bin/python3
# coding=utf-8
'''
Description: Description
Author: Stream
Version: V0.0.1
Date: 2020-09-15 14:59:59
LastEditors: Stream
LastEditTime: 2020-09-15 15:59:25
FilePath: \code\python\hotmap.py
ChangeLog: ChangeLog
'''

import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
 
data = np.array([[1,2,3],[4,5,6],[7,8,9]])
sns.heatmap(data,annot=True)
plt.show()
