"""
[두 개의 정렬된 배열 nums1과 nums2가 주어졌을 때, 
    두 배열을 합쳐서 중간값(median)을 찾는 함수]
Given two sorted arrays nums1 and nums2 of size m and n respectively, 
return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).



Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

"""

def findMedianSortedArrays(nums1: list[int], nums2: list[int]) -> float:
    # nums1의 내용을 새로운 리스트인 list에 복사합니다.
    list = nums1
    # nums2의 내용을 list에 추가(확장)합니다.
    list.extend(nums2)
    # list를 정렬합니다.
    list.sort()

    # list의 길이(크기)를 구합니다.
    list_length = len(list)
    # 중간 인덱스를 구합니다.
    ind = list_length//2

    # list의 길이가 짝수일 경우
    if len(list)%2 ==0:
        # 중간에 위치한 두 숫자의 평균값을 중간값으로 설정합니다.
        med = (list[ind-1] + list[ind])/2
    # list의 길이가 홀수일 경우
    else:
        # 중간에 위치한 숫자를 중간값으로 설정합니다.
        med = list[ind]
    
    # 계산된 중간값을 반환합니다.
    return med
