/*
void merge_sort(int *elements, int elements_size)
{
     int element_index = 0;
     while(element_index < elements_size)
    {
        if(element_index + 1 >= element_size)
           ra
        compare elements[i] and i+1
         swap if i > i+1, then rotateA twice
         element_index += 2;
    }

     int * stack_b;
     element_index = 0;
     while(element_index < ceil((double)elements_size/2.0))
    {
         if element[i] < element[i+1] sa then pb
         compare elements of b, swap if new element is bigger
         element_index +=1
    }


}
*/

/*
initial state                   -> [5, 3, 4, 1, 2, 6, 7]
element_i = 0 -> sa ra ra   -> [3, 5, 4, 1, 2, 6, 7]
element_i = 2 -> sa ra ra   -> [3, 5, 1, 4, 2, 6, 7]
element_i = 4 ->    ra ra
element_i = 6 ->       ra


actual state             -> A [3, 5, 1, 4, 2, 6, 7] | B [_, _, _, _, _, _, _]
element_i = 0 -> sa pb   -> A [_, 3, 1, 4, 2, 6, 7] | B [_, _, _, _, _, _, 5]
element_i = 1 ->    pb   -> A [_, _, 1, 4, 2, 6, 7] | B [_, _, _, _, _, 3, 5]
element_i = 2 -> sa pb sb-> A [_, _, _, 1, 2, 6, 7] | B [_, _, _, _, 3, 4, 5]
element_i = 3 ->    pb   -> A [_, _, _, _, 2, 6, 7] | B [_, _, _, 1, 3, 4, 5]

actual state              -> A [_, _, _, _, 2, 6, 7] | B [_, _, _, 1, 3, 4, 5]
element_i = 0 -> pa ra    -> A [_, _, _, 2, 6, 7, 1] | B [_, _, _, _, 3, 4, 5]
element_i = 1 -> ra       -> A [_, _, _, 6, 7, 1, 2] | B [_, _, _, _, 3, 4, 5]
element_i = 2 -> pa ra    -> A [_, _, 6, 7, 1, 2, 3] | B [_, _, _, _, _, 4, 5]
element_i = 3 -> pa ra    -> A [_, 6, 7, 1, 2, 3, 4] | B [_, _, _, _, _, _, 5]
element_i = 3 -> pa       -> A [5, 6, 7, 1, 2, 3, 4] | B [_, _, _, _, _, _, _]
element_i = 3 -> ra ra ra -> A [1, 2, 3, 4, 5, 6, 7] | B [_, _, _, _, _, _, _]





initial state         -> A [5, 1, 2, 4, 3] | B [_, _, _, _, _]
pa                    -> A [_, 1, 2, 4, 3] | B [_, _, _, _, 5]
ra ra                 -> A [_, 4, 3, 1, 2] | B [_, _, _, _, 5]
sa                    -> A [_, 3, 4, 1, 2] | B [_, _, _, _, 5]
ra ra                 -> A [_, 1, 2, 3, 4] | B [_, _, _, _, 5]
pa ra                 -> A [1, 2, 3, 4, 5] | B [_, _, _, _, _]

sa sb ss ra rb rr rra rrb rrr pa pb
*/