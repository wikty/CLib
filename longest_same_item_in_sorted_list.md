##描述##

从已排序数组中找出其中所含相同元素的最长序列

##示例##

输入： 一个已经排序的序列

        `l = [2, 2, 2, 3, 5, 6, 6, 6, 6, 7]`

输出： (start, length)，最长相同元素序列的开始索引和长度

        `(5, 4)`, 因为其中相同元素最长序列为`[6, 6, 6, 6]`，此序列第一个元素的索引为5，序列长度为4

##代码##

        def test(lst):
            lst = sorted(lst)  # make sure lst is sorted
            longest = 0
            last = 0
            for i,item in enumerate(lst):
                if lst[i-longest] == item:
                    longest += 1
                    last = i
            return (last-longest+1, longest)
