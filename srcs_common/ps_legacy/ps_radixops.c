/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_radixops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:49:47 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 09:49:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int twopow(int nbr)
{
    int res = 2;

    if (nbr == 0)
        return (1);
    while (nbr-- > 1)
        res *= 2;
    return (res);
}

int totalzeros(int size, int bit)
{
    int division;
    int mod;
    int power;
    int ones;
    int left;

    power = twopow(bit + 1);
    division = size / power;
    mod = size % power;
    ones = power / 2;
    if (mod > ones)
        left = (mod - ones);
    else
        left = 0;
    return (size - (division * ones + left));
}

int total_radix_ops(int size)
{
    int max_bits;
    int i;
    int res;

    max_bits = 0;
    while ((size - 1) >> max_bits)
        max_bits++;
    res = size * max_bits;
    i = 0;
    while (i < max_bits)
        res += totalzeros(size, i++);
    return (res);
}
