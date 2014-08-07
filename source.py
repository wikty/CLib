def longest_same_item_in_sorted_list(lst):
    lst = sorted(lst)  # make sure lst is sorted
    longest = 0
    last = 0
    for i,item in enumerate(lst):
        if lst[i-longest] == item:
            longest += 1
            last = i
    return (last-longest+1, longest)

def compare_two_sorted_array_greater(lst1, lst2):
    lst1 = sorted(lst1)
    lst2 = sorted(lst2)  # mark sure list is sorted
    idx1 = 0
    idx2 = 0
    lst1_len = len(lst1)
    lst2_len = len(lst2)
    count = 0
    while idx1<lst1_len and idx2<lst2_len:
        if lst1[idx1] > lst2[idx2]:
            count += lst1_len - idx1
            idx2 += 1
        else:
            idx1 += 1
    return count

def compare_two_sorted_array_equal(lst1, lst2):
    lst1 = sorted(lst1)
    lst2 = sorted(lst2)  # mark sure list is sorted
    idx1 = 0
    idx2 = 0
    lst1_len = len(lst1)
    lst2_len = len(lst2)
    count = 0
    while idx1<lst1_len and idx2<lst2_len:
        if lst1[idx1] > lst2[idx2]:
            idx2 += 1
        elif lst1[idx1] < lst2[idx2]:
            idx1 += 1
        else:
            count += 1
            idx1 += 1
            idx2 += 1
    return count

def compare_two_sorted_array_distance(lst1, lst2):
    lst1 = sorted(lst1)
    lst2 = sorted(lst2)  # mark sure list is sorted
    idx1 = 0
    idx2 = 0
    lst1_len = len(lst1)
    lst2_len = len(lst2)
    min_distance = max(lst1+lst2) + 1
    while idx1<lst1_len and idx2<lst2_len:
        distance = abs(lst1[idx1]-lst2[idx2])
        if distance < min_distance:
            min_distance = distance
        if lst1[idx1] > lst2[idx2]:
            idx2 += 1
        elif lst1[idx1] < lst2[idx2]:
            idx1 += 1
        else:
            return 0
    return min_distance

def array_prefix_suffix_sum_equal(lst):
    count = 0
    head_idx = 0
    tail_idx = len(lst) - 1
    
    prefix_sum = 0
    suffix_sum = 0
    
    while head_idx < len(lst) or tail_idx > -1:
        prefix_sum += lst[head_idx]
        suffix_sum += lst[tail_idx]
        if prefix_sum > suffix_sum:
            prefix_sum -= lst[head_idx]
            tail_idx -= 1
        elif prefix_sum < suffix_sum:
            suffix_sum -= lst[tail_idx]
            head_idx += 1            
        else:
            count += 1
            head_idx += 1
            tail_idx -= 1
    return count
