#include "usage.h"

int				usage(char **argv)
{
	ft_printf("{yellow}\t\t\t\t\tUsage:{eoc}\n"
		"\t%s [-n <number 1 .. 4> player.cor] [-v] "
		"[-dump <number>] [-debug <number>] player.cor\n"
		"\t-h - --help - print this message\n"
		"\t-v - for enable visual mode\n"
		"\t-n - to set different player number\n"
		"\t-m - mute\n"
		"\t-dump - print dump of memory at some cycle, to stdout\n"
		"\t-debug - debug level\n"
		"\t\t- 0 : show only winner (default)\n"
		"\t\t- 1 : show lives\n", argv[0]);
	return (1);
}

int				check_players_file_name(t_data *data)
{
	int			i;
	char		*p;

	i = 0;
	while (++i < (MAX_PLAYERS + 1) && i < (data->bots_count + 1))
	{
		p = 0;
		ft_printf("%s\n", data->players[i]);
		(data->players[i]) ? (p = ft_strrchr(data->players[i], '.')) : 0;
		if (p)
		{
			if (p[1] != 'c' || p[2] != 'o' || p[3] != 'r' || p[4] != '\0')
			{
				ft_printf("{red}Wrong player name '%s'{eoc}\n",
						data->players[i]);
				return (1);
			}
		}
		else
		{
			ft_printf("{red}Empty slot for player # %d\n{eoc}", i);
			return (1);
		}
	}
	return (0);
}
