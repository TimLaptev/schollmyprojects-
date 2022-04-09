import cv2
import numpy as np

img = cv2.imread("input.png")
fn="input.png"
img_grey = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
thresh = 100
ret,thresh_img = cv2.threshold(img_grey, thresh, 255, cv2.THRESH_BINARY)
contours, hierarchy = cv2.findContours(thresh_img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
img_contours = np.zeros(img.shape)
cv2.drawContours(img_contours, contours, -1, (0,250,0), 5)
cv2.imwrite("img2.png",img_contours)