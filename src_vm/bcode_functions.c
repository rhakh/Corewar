#include "bcode_functions.h"

int			get_number_from_bcode(const unsigned char *code, int num_size)
{
	int				i;
	int				num;
	unsigned char	*pnum;

	num = 0;
	pnum = (unsigned char *)(&num);
	i = 0;
	code += num_size - 1;
	while (i < num_size)
	{
		*pnum = *code;
		code--;
		pnum++;
		i++;
	}
	return ((num_size == 2) ? ((short)num) : (num));
}

int			put_number_to_bcode(t_data *data, int num, int position)
{
	int				i;
	unsigned char	*pnum;

	i = 0;
	pnum = (unsigned char *)&num;
	position += 3;
	while (i < DIR_SIZE)
	{
		*(data->map + ((position + MEM_SIZE) % MEM_SIZE)) = *pnum;
		i++;
		pnum++;
		position--;
	}
	return (0);
}
