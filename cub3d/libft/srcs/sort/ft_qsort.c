/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:00:55 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/08 15:31:05 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** ft_qsort() Sorts an array of integers in ascending order using an optimized
 * QuickSort.
 *
 * @array: Pointer to the integer array.
 * @size: Number of elements in the array.
 *
 * How it works / Notes:
 *  - Uses Median-of-Three pivot selection to mitigate worst-case behavior on
 * partially sorted data.
 *  - Switches to Insertion Sort for small sub-arrays
 * (below QSORT_THRESHOLD) to improve performance.
 *  - Implements tail recursion optimization to reduce overall call depth.
 *
 * Usage:
 *  - Call ft_qsort(array, size) for any array of integers you need in
 * ascending order.
 *  - This is suitable for large datasets but remains efficient for moderate
 * sizes too.
 *  - Ensure 'array' is valid and 'size' > 1; otherwise, the function
 * returns immediately.
 */

#define QSORT_THRESHOLD 10

/*
 * Insertion sort for small partitions.
 * Efficient for tiny sub-arrays and helps avoid overhead
 * of deeper QuickSort recursion on these ranges.
 */
static void	insertion_sort(int *array, int start, int end)
{
	int	i;
	int	j;
	int	key;

	i = start + 1;
	while (i <= end)
	{
		key = array[i];
		j = i - 1;
		while (j >= start && array[j] > key)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
		i++;
	}
}

/*
 * Median-of-three selection: ensures a better pivot for typical data
 * distributions.
 * Places the chosen pivot at array[end] for partitioning.
 */
static int	median_of_three(int *array, int start, int end)
{
	int	mid;

	mid = (start + end) / 2;
	if (array[start] > array[mid])
		ft_swap(&array[start], &array[mid], sizeof(int));
	if (array[start] > array[end])
		ft_swap(&array[start], &array[end], sizeof(int));
	if (array[mid] > array[end])
		ft_swap(&array[mid], &array[end], sizeof(int));
	return (array[end]);
}

/*
 * Partition around a pivot, elements less than pivot on the left,
 * greater on the right. Returns final pivot index.
 */
static int	partition(int *array, int start, int end)
{
	int	pivot_value;
	int	i;
	int	j;

	pivot_value = median_of_three(array, start, end);
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (array[j] < pivot_value)
		{
			i++;
			ft_swap(&array[i], &array[j], sizeof(int));
		}
		j++;
	}
	ft_swap(&array[i + 1], &array[end], sizeof(int));
	return (i + 1);
}

/*
 * QuickSort using:
 *  - Insertion sort for small sub-arrays, it's faster.
 *  - Tail recursion optimization on larger sub-arrays, sorting the smaller half
 *  first to reduce recursion depth.
 */
static void	quicksort(int *array, int start, int end)
{
	int	pivot;

	while (start < end)
	{
		if ((end - start + 1) < QSORT_THRESHOLD)
		{
			insertion_sort(array, start, end);
			break ;
		}
		pivot = partition(array, start, end);
		if ((pivot - 1) - start < end - (pivot + 1))
		{
			quicksort(array, start, pivot - 1);
			start = pivot + 1;
		}
		else
		{
			quicksort(array, pivot + 1, end);
			end = pivot - 1;
		}
	}
}

void	ft_qsort(int *array, int size)
{
	if (!array || size <= 1)
		return ;
	quicksort(array, 0, size - 1);
}
