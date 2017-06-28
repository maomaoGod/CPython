# -*- coding: utf-8 -*-
#author @zhongrui
#time   @20170628
#locate @hust
#release under the same license as python3.5

import time

class ClockTimer():
    """a timer class"""
    __slots__ = ('__start', '__stop', '__second', '__startTimer')
    # property
    # __start = 0
    # __stop = 0
    # __second = 0
    # __startTimer = False

    # class member func
    def __init__(self):
        self.__second = 0
        self.__startTimer = False
        self.__start = 0
        self.__stop = 0
        
    def __str__(self):
        if self.__startTimer:
            return "timer already run %d seconds"%self.__second
        else:
            return "timer is not start"

    __repr__ = __str__

    def start(self):
        if self.__startTimer:
            print("timer is already started")
        else:
            self.__start = time.localtime()
            self.__startTimer = True
            self.__second = 0
            print("start timer...")

    def stop(self):
        if self.__startTimer:
            self.__stop = time.localtime()
            self.__startTimer = False
            self.__elapse__()
            print("stop timer...")
        else:
            print("timer is not started,please call start first")

    def __add__(self,other):
        return self.__second+other.__second
            
    def __elapse__(self):
        last = []
        elapse = 0
        for index in range(6):
            last.append(self.__stop[index] - self.__start[index])
            if index == 0:
                elapse+= last[index]*365*24*3600
            if index == 1:
                elapse += last[index]*30*24*3600
            if index == 2:
                elapse += last[index]*24*3600
            if index == 3:
                elapse += last[index]*3600
            if index == 4:
                elapse += last[index]*60
            if index == 5:
                elapse += last[index]
        self.__second = elapse

    def get_timer(self):
        return self.__second

    @property
    def timer(self):
        return self.__second
