#include "main.h"

char 		get_op_code(char arg_type[3])
{
	char 	op;
	int 	i;

	i = 0;
	op = 0;
	while (i < 3)
	{
		(arg_type[i] == T_REG) ?
					(op = ((char)REG_CODE << (6 - i * 2)) | op) : 0;
		(arg_type[i] == T_DIR) ?
					(op = ((char)DIR_CODE << (6 - i * 2)) | op) : 0;
		(arg_type[i] == T_IND) ?
					(op = ((char)IND_CODE << (6 - i * 2)) | op) : 0;
		i++;
	}
	return (op);
}
