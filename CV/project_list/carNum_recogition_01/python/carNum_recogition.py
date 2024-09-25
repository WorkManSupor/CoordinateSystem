#=================================================================#
#                    RECOGITION CORE ALGORITHM                    #
#    OPENCV BASE FUNCTION: load image(*jpg)                       #
#    DESCRIPTION         : only funciton unit                     #
#    INPUT VALUE         :                                        #
#=================================================================#
# sys, base hpp
#=================================================================#
import matplotlib.pyplot as plt
import numpy as np
#=================================================================#
# lib import
#=================================================================#
import cv2
#=================================================================#
def sort_contours(cnt_s, method="left-to-right"):
    reverse = False
    ii_myutils = 0
    if method == "right-to-left" or method == "bottom-to-top":
        reverse = True
    if method == "top-bottom" or method == "bottom-to-top":
        ii_myutils = 1
    bounding_boxes = [cv2.boundingRect(cc_myutils) for cc_myutils in cnt_s] # user oone
    (cnt_s, bounding_boxes) = zip(*sorted(zip(cnt_s, bounding_boxes),key = lambda b: b[1][ii_myutils],reverse=reverse))
    return cnt_s, bounding_boxes
def resize(image, width=None, height=None, inter=cv2.INTER_AREA):
    dim_myutils = None
    (h_myutils, w_myutils) = image.shape[:2]
    if width is None and height is None:
        return image
    if width is None:
        r_myutils = height / float(h_myutils)
        dim_myutils = (int(w_myutils * r_myutils),height)
    else:
        r_myutils = width / float(w_myutils)
        dim_myutils = (width, int(h_myutils * r_myutils))
    resized = cv2.resize(image, dim_myutils, interpolation = inter)
    return resized

def extract_template(image):
    """(1) pick num from mode image"""
    ref_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    


#=================================================================#
#                           NO_MORE                               #
#=================================================================#