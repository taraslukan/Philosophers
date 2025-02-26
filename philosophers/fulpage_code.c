#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#define ERROR 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo t_philo;
// Struttura per rappresentare un filosofo
typedef struct s_first {
	t_philo 		*philo;
	int 			nphilo;
	int 			n_o_t_e_p_m_e;
	int 			ttsleap;
	int		 		tteat;
	int 			ttdie;
	int				ifdie;
	size_t			strtme;
	pthread_t		monitor;
	pthread_mutex_t	*thefork;
	pthread_mutex_t	ckdie;
} t_first;

typedef struct s_philo {
	int				id;
	pthread_mutex_t	ckeat;
	pthread_t		thread;
	int				counteat;
	size_t			cktmeat;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	t_first			*first;
} t_philo;


// Funzione principale del filosofo
// void	*monitor_routine(void *arg);
// void	*strroutin(void *gen);
// size_t	get_current_time(void);
// void	readystruct(int ac, char **av, t_first *first);
// void	initphilostr(t_first *first);
// void	mallocthreadfirst(t_first *first);
// void	print_action(t_philo *philo, const char *action);
// void	startreading(t_first *first);
// void	put_down_forks(t_philo *philo);
// void	eat(t_philo *philo);
// void	print_action(t_philo *philo, const char *action);
// void	take_forks(t_philo *philo);
// int		ft_atoi(const char *str);
// int		check(int argc, char **argv);


#endif


#include "../philosophers.h"

void	*monitor_routine(void *arg);
void	*strroutin(void *gen);
size_t	get_current_time(void);
void	readystruct(int ac, char **av, t_first *first);
void	initphilostr(t_first *first);
void	mallocthreadfirst(t_first *first);
void	print_action(t_philo *philo, const char *action);
void	startreading(t_first *first);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	print_action(t_philo *philo, const char *action);
void	take_forks(t_philo *philo);
int		ft_atoi(const char *str);
int		check(int argc, char **argv);


// void	print_action(t_philo *philo, const char *action)
// {
// 	t_first *first = philo->first;

// 	pthread_mutex_lock(&first->ckdie); // Protezione durante la stampa
// 	if (!first->ifdie) // Controlla che nessuno sia morto
// 		printf("%zu %d %s\n", get_current_time() - first->strtme, philo->id + 1, action);
// 	pthread_mutex_unlock(&first->ckdie); // Rilascia il mutex
// }


void	*strroutin(void *gen)
{
	t_philo	*philo;
	t_first	*first;

	philo = (t_philo *)gen;
	first = philo->first;

	while (!first->ifdie) // Il filosofo opera finché nessuno muore
	{
		// 1. Pensare
		print_action(philo, "is thinking");

		// 2. Prendere le forchette
		take_forks(philo);

		// 3. Mangiare
		eat(philo);

		// 4. Rilasciare le forchette
		put_down_forks(philo);

		// 5. Dormire
		print_action(philo, "is sleeping");
		usleep(first->ttsleap * 1000); // Tempo di sonno
	}
	return (NULL); // Terminazione del thread
}

void	startreading(t_first *first)
{
	int	i;

	i = 0;
	while (i < first->nphilo)
	{
		pthread_create(&first->philo[i].thread, NULL, &strroutin, &first->philo[i]);
		i++;
	}
	pthread_create(&first->monitor, NULL, &monitor_routine, first);
	i = 0;
	while (i < first->nphilo)
	{
		pthread_join(first->philo[i].thread, NULL);
		i++;
	}
	pthread_join(first->monitor, NULL);
}


size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void readystruct(int ac, char **av, t_first *first)
{
	first->nphilo = ft_atoi(av[1]);
	first->ttdie = ft_atoi(av[2]);
	first->tteat = ft_atoi(av[3]);
	first->ttsleap = ft_atoi(av[4]);
	first->strtme = get_current_time();
	if (ac == 6)
		first->n_o_t_e_p_m_e = ft_atoi(av[5]);
	else
		first->n_o_t_e_p_m_e = -1;
	first->ifdie = 0;
	mallocthreadfirst(first);
	initphilostr(first);
}

void initphilostr(t_first *first)
{
	int	i;
	
	i = 0;
	first->philo = (t_philo *)malloc(sizeof(t_philo) * first->nphilo);
	if (first->philo == NULL)
		return;
	while (i < first->nphilo)
	{
		first->philo[i].id = i + 1;
		first->philo[i].counteat = 0;
		first->philo[i].cktmeat = first->strtme;
		first->philo[i].lfork = &first->thefork[i];
		if (first->nphilo == 1)
			first->philo[i].rfork = NULL;
		else if (i < first->nphilo - 1)
			first->philo[i].rfork = &first->thefork[i + 1];
		else
			first->philo[i].rfork = &first->thefork[0];
		first->philo[i].first = first;
		pthread_mutex_init(&first->philo[i].ckeat, NULL);
		i++;	
	}	
}

void mallocthreadfirst(t_first *first)
{
	int i;
	
	i = 0;
	pthread_mutex_init(&first->ckdie, NULL);
	first->thefork = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * first->nphilo);
	if (first->thefork == NULL)
		return ;
	while (i < first->nphilo)
	{
		pthread_mutex_init(&first->thefork[i], NULL);
		i++;
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	if (philo->rfork)
		pthread_mutex_unlock(philo->rfork);
}

void	eat(t_philo *philo)
{
	t_first	*first = philo->first;

	pthread_mutex_lock(&philo->ckeat);
	philo->cktmeat = get_current_time();
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->ckeat);
	usleep(first->tteat * 1000);
	philo->counteat++;
	// if (first->n_o_t_e_p_m_e != -1 && philo->counteat >= first->n_o_t_e_p_m_e)
	// {
	// 	//controllo N_O_T_E_P_M_E
	// }
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_action(philo, "has taken a left fork");
	if (philo->rfork)
	{
		pthread_mutex_lock(philo->rfork);
		print_action(philo, "has taken a right fork");
	}
}

void	print_action(t_philo *philo, const char *action)
{
	t_first *first = philo->first;

	pthread_mutex_lock(&first->ckdie); // Protezione durante la stampa
	if (!first->ifdie) // Controlla che nessuno sia morto
		printf("%zu %d %s\n", get_current_time() - first->strtme, philo->id, action);
	pthread_mutex_unlock(&first->ckdie); // Rilascia il mutex
}


void	*monitor_routine(void *arg)
{
	t_first *first;
	int		i;

	first = (t_first *)arg;
	while (!first->ifdie)
	{
		i = 0;
		while (i < first->nphilo)
		{
			pthread_mutex_lock(&first->philo[i].ckeat);
			if (get_current_time() - first->philo[i].cktmeat > (size_t)first->ttdie)
			{
				first->ifdie = 1;
				print_action(&first->philo[i], "died");
			}
			pthread_mutex_unlock(&first->philo[i].ckeat);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

// Ingresso principale del programma
int main(int argc, char **argv)
{
	t_first	first;
	
	if (check(argc, argv))
		return(ERROR);
	// TODO: Inizializzazione dei filosofi e avvio dei thread
	readystruct(argc, argv, &first);
	return 0;
}

int	check(int argc, char **argv)
{
	//check generale sulle formalitá
	int i;
	int y;
	
	i = 1;
	y = 0;
	if (argc < 5 || argc > 6)
		return (ERROR);
	while (argv[i][y])
	{
		while (argv[i][y])
		{
			if (!(argv[i][y] >= '0' && argv[i][y] <= '9'))
				return (ERROR);
			y++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		str++;
	}
	return ((int)(result * sign));
}



{"IdSoggetto":1925190,"AuthToken":"e9310a4d-47ec-40ff-84e6-db582b3da4eb","IdUtente":2974508,"SessionStatus":0,"Username":"Taras99","Nome":"ALEX","Cognome":"CUCINA","Email":"alexcucina99@libero.it","CodiceFiscale":"CCNLXA99R14C573K","UltimoAccesso":"2022-07-08T12:18:49","TentativiRimasti":0,"Saldo":129660,"SaldoPrelevabile":129660,"SaldoBonus":0,"SaldoBonusRigioco":0,"SaldoPlayBonus":0,"CambioPasswordObbligatorio":true,"InserimentoDomandaSegretaObbligatorio":false,"AccettazioneConsensiMarketingObbligatorio":true,"AutolimitazioneObbligatoria":false,"MessaggiAltaPriorita":false,"UtenteMigrato":true,"IdSpecializzazione":36,"CodiceContratto":"0004263935","AutoesclusioneAttiva":false,"Sesso":"M","DataNascita":"1999-10-14T00:00:00","Telefono":"00393275482538","Citta":"Rimini","IdRegioneResidenza":8,"IdRichiestaIovation":0,"BTAG":null,"HtmlPopupPostLogin":null,"ValidazioneContatti":1,"Brand":2,"DestinationUrl":null,"UtenteLTM":true,"PromoBenvenutoRetail":null,"PreferenzaInvioOTP":null,"DescPreferenzaInvioOTP":null,"FlgRicezioneOTP":null,"RecapitoPredefinitoIovation":null,"IdOrigineRegistrazione":0,"FlgRegistrazioneTipster":false,"IdTipoStatoTipster":null,"FlgCondivisioneAutomaticaTipster":null,"BS":true,"GruppoLamp":null,"ListIdTipoBS":[1],"CategoryCluster":[],"Vgh":false,"Message":"Success","ResultCode":0,"Skip":true,"MenuCdg":[{"Title":"Storico Conto","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Lista Giocate","DestinationUrl":"","IdDestination":6,"Children":null,"AzioniDaCompletare":0},{"Title":"Lista Movimenti","DestinationUrl":"","IdDestination":5,"Children":null,"AzioniDaCompletare":0},{"Title":"Storico Accessi","DestinationUrl":"","IdDestination":17,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":0},{"Title":"Profilo","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Dati Personali","DestinationUrl":"","IdDestination":4,"Children":null,"AzioniDaCompletare":2},{"Title":"Sicurezza","DestinationUrl":"","IdDestination":9,"Children":null,"AzioniDaCompletare":0},{"Title":"Contratto di gioco","DestinationUrl":"","IdDestination":14,"Children":null,"AzioniDaCompletare":0},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"Privacy","DestinationUrl":"","IdDestination":12,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":2},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"FAQ","DestinationUrl":"","IdDestination":62,"Children":null,"AzioniDaCompletare":0},{"Title":"Contatti","DestinationUrl":"","IdDestination":37,"Children":null,"AzioniDaCompletare":0}]}
{"IdSoggetto":4780149,"AuthToken":"0f49e178-cf23-4394-af80-1bde97828f9c","IdUtente":5820405,"SessionStatus":0,"Username":"Tarallo99","Nome":"TARAS","Cognome":"LUKAN","Email":"Taras99lukan@gmail.com","CodiceFiscale":"LKNTRS99M21Z138U","UltimoAccesso":"2024-11-28T15:17:05.327","TentativiRimasti":0,"Saldo":7,"SaldoPrelevabile":7,"SaldoBonus":700,"SaldoBonusRigioco":0,"SaldoPlayBonus":0,"CambioPasswordObbligatorio":false,"InserimentoDomandaSegretaObbligatorio":false,"AccettazioneConsensiMarketingObbligatorio":false,"AutolimitazioneObbligatoria":false,"MessaggiAltaPriorita":false,"UtenteMigrato":false,"IdSpecializzazione":33,"CodiceContratto":"15017-5632238","AutoesclusioneAttiva":false,"Sesso":"M","DataNascita":"1999-08-21T00:00:00","Telefono":"3209539109","Citta":"Spoleto","IdRegioneResidenza":10,"IdRichiestaIovation":314903150,"BTAG":null,"HtmlPopupPostLogin":null,"ValidazioneContatti":0,"Brand":2,"DestinationUrl":null,"UtenteLTM":false,"PromoBenvenutoRetail":null,"PreferenzaInvioOTP":2,"DescPreferenzaInvioOTP":"Documento","FlgRicezioneOTP":null,"RecapitoPredefinitoIovation":null,"IdOrigineRegistrazione":1,"FlgRegistrazioneTipster":false,"IdTipoStatoTipster":null,"FlgCondivisioneAutomaticaTipster":null,"BS":false,"GruppoLamp":null,"ListIdTipoBS":[],"CategoryCluster":[],"Vgh":false,"Message":"Success","ResultCode":0,"Skip":true,"MenuCdg":[{"Title":"Storico Conto","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Lista Giocate","DestinationUrl":"","IdDestination":6,"Children":null,"AzioniDaCompletare":0},{"Title":"Lista Movimenti","DestinationUrl":"","IdDestination":5,"Children":null,"AzioniDaCompletare":0},{"Title":"Storico Accessi","DestinationUrl":"","IdDestination":17,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":0},{"Title":"Profilo","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Dati Personali","DestinationUrl":"","IdDestination":4,"Children":null,"AzioniDaCompletare":0},{"Title":"Sicurezza","DestinationUrl":"","IdDestination":9,"Children":null,"AzioniDaCompletare":0},{"Title":"Contratto di gioco","DestinationUrl":"","IdDestination":14,"Children":null,"AzioniDaCompletare":0},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"Privacy","DestinationUrl":"","IdDestination":12,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":0},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"FAQ","DestinationUrl":"","IdDestination":62,"Children":null,"AzioniDaCompletare":0},{"Title":"Contatti","DestinationUrl":"","IdDestination":37,"Children":null,"AzioniDaCompletare":0}],"HasHistoryBonus":true,"Bonus":[{"IdBonus":90,"NomeCampagna":"Promo Multi Bonus","BonusErogato":300,"BonusDisponibile":300,"TipoBonusDescrizione":"Real","DataScadenza":"2024-12-07T12:40:01.56","DataErogazione":"0001-01-01T00:00:00","UrlTerminiECondizioni":null,"Verticale":3,"GiriGratuitiResidui":null,"TipoBonus":1,"BonusRigiocoPuntato":null,"PercentualeRigioco":null,"TurnoverSbloccaBonus":null,"Wagering":null,"DescrizioneBonusBO":"Bonus Slot validità 3 giorni"},{"IdBonus":406,"NomeCampagna":"Bonus Lotterie","BonusErogato":100,"BonusDisponibile":100,"TipoBonusDescrizione":"Real","DataScadenza":"2024-12-09T13:00:02.91","DataErogazione":"0001-01-01T00:00:00","UrlTerminiECondizioni":null,"Verticale":12,"GiriGratuitiResidui":null,"TipoBonus":1,"BonusRigiocoPuntato":null,"PercentualeRigioco":null,"TurnoverSbloccaBonus":null,"Wagering":null,"DescrizioneBonusBO":"Bonus Lotterie 5 giorni"},{"IdBonus":529,"NomeCampagna":"Promo Multi Bonus","BonusErogato":300,"BonusDisponibile":300,"TipoBonusDescrizione":"Real","DataScadenza":"2024-12-07T12:40:01.56","DataErogazione":"0001-01-01T00:00:00","UrlTerminiECondizioni":null,"Verticale":1,"GiriGratuitiResidui":null,"TipoBonus":1,"BonusRigiocoPuntato":null,"PercentualeRigioco":null,"TurnoverSbloccaBonus":null,"Wagering":null,"DescrizioneBonusBO":"Bonus Sport 4 eventi quota 2.5 validità 3 giorni"}]}


{"IdSoggetto":4780149,"AuthToken":"670dd259-c104-46e9-bf69-c8c4bd1e1590","IdUtente":5820405,"SessionStatus":0,"Username":"Tarallo99","Nome":"TARAS","Cognome":"LUKAN","Email":"Taras99lukan@gmail.com","CodiceFiscale":"LKNTRS99M21Z138U","UltimoAccesso":"2024-12-04T17:14:21.56","TentativiRimasti":0,"Saldo":7,"SaldoPrelevabile":7,"SaldoBonus":700,"SaldoBonusRigioco":0,"SaldoPlayBonus":0,"CambioPasswordObbligatorio":false,"InserimentoDomandaSegretaObbligatorio":false,"AccettazioneConsensiMarketingObbligatorio":false,"AutolimitazioneObbligatoria":false,"MessaggiAltaPriorita":false,"UtenteMigrato":false,"IdSpecializzazione":33,"CodiceContratto":"15017-5632238","AutoesclusioneAttiva":false,"Sesso":"M","DataNascita":"1999-08-21T00:00:00","Telefono":"3209539109","Citta":"Spoleto","IdRegioneResidenza":10,"IdRichiestaIovation":314919001,"BTAG":null,"HtmlPopupPostLogin":null,"ValidazioneContatti":0,"Brand":2,"DestinationUrl":null,"UtenteLTM":false,"PromoBenvenutoRetail":null,"PreferenzaInvioOTP":2,"DescPreferenzaInvioOTP":"Documento","FlgRicezioneOTP":null,"RecapitoPredefinitoIovation":null,"IdOrigineRegistrazione":1,"FlgRegistrazioneTipster":false,"IdTipoStatoTipster":null,"FlgCondivisioneAutomaticaTipster":null,"BS":false,"GruppoLamp":null,"ListIdTipoBS":[],"CategoryCluster":[],"Vgh":false,"Message":"Success","ResultCode":0,"Skip":true,"MenuCdg":[{"Title":"Storico Conto","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Lista Giocate","DestinationUrl":"","IdDestination":6,"Children":null,"AzioniDaCompletare":0},{"Title":"Lista Movimenti","DestinationUrl":"","IdDestination":5,"Children":null,"AzioniDaCompletare":0},{"Title":"Storico Accessi","DestinationUrl":"","IdDestination":17,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":0},{"Title":"Profilo","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Dati Personali","DestinationUrl":"","IdDestination":4,"Children":null,"AzioniDaCompletare":0},{"Title":"Sicurezza","DestinationUrl":"","IdDestination":9,"Children":null,"AzioniDaCompletare":0},{"Title":"Contratto di gioco","DestinationUrl":"","IdDestination":14,"Children":null,"AzioniDaCompletare":0},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"Privacy","DestinationUrl":"","IdDestination":12,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":0},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"FAQ","DestinationUrl":"","IdDestination":62,"Children":null,"AzioniDaCompletare":0},{"Title":"Contatti","DestinationUrl":"","IdDestination":37,"Children":null,"AzioniDaCompletare":0}],"HasHistoryBonus":true,"Bonus":[{"IdBonus":90,"NomeCampagna":"Promo Multi Bonus","BonusErogato":300,"BonusDisponibile":300,"TipoBonusDescrizione":"Real","DataScadenza":"2024-12-07T12:40:01.56","DataErogazione":"0001-01-01T00:00:00","UrlTerminiECondizioni":null,"Verticale":3,"GiriGratuitiResidui":null,"TipoBonus":1,"BonusRigiocoPuntato":null,"PercentualeRigioco":null,"TurnoverSbloccaBonus":null,"Wagering":null,"DescrizioneBonusBO":"Bonus Slot validità 3 giorni"},{"IdBonus":406,"NomeCampagna":"Bonus Lotterie","BonusErogato":100,"BonusDisponibile":100,"TipoBonusDescrizione":"Real","DataScadenza":"2024-12-09T13:00:02.91","DataErogazione":"0001-01-01T00:00:00","UrlTerminiECondizioni":null,"Verticale":12,"GiriGratuitiResidui":null,"TipoBonus":1,"BonusRigiocoPuntato":null,"PercentualeRigioco":null,"TurnoverSbloccaBonus":null,"Wagering":null,"DescrizioneBonusBO":"Bonus Lotterie 5 giorni"},{"IdBonus":529,"NomeCampagna":"Promo Multi Bonus","BonusErogato":300,"BonusDisponibile":300,"TipoBonusDescrizione":"Real","DataScadenza":"2024-12-07T12:40:01.56","DataErogazione":"0001-01-01T00:00:00","UrlTerminiECondizioni":null,"Verticale":1,"GiriGratuitiResidui":null,"TipoBonus":1,"BonusRigiocoPuntato":null,"PercentualeRigioco":null,"TurnoverSbloccaBonus":null,"Wagering":null,"DescrizioneBonusBO":"Bonus Sport 4 eventi quota 2.5 validità 3 giorni"}]}
{"IdSoggetto":1925190,"AuthToken":"2d45791f-5a4c-495e-9072-59d684e55b9b","IdUtente":2974508,"SessionStatus":0,"Username":"Taras99","Nome":"ALEX","Cognome":"CUCINA","Email":"alexcucina99@libero.it","CodiceFiscale":"CCNLXA99R14C573K","UltimoAccesso":"2022-07-08T12:18:49","TentativiRimasti":0,"Saldo":129660,"SaldoPrelevabile":129660,"SaldoBonus":0,"SaldoBonusRigioco":0,"SaldoPlayBonus":0,"CambioPasswordObbligatorio":true,"InserimentoDomandaSegretaObbligatorio":false,"AccettazioneConsensiMarketingObbligatorio":true,"AutolimitazioneObbligatoria":false,"MessaggiAltaPriorita":false,"UtenteMigrato":true,"IdSpecializzazione":36,"CodiceContratto":"0004263935","AutoesclusioneAttiva":false,"Sesso":"M","DataNascita":"1999-10-14T00:00:00","Telefono":"00393275482538","Citta":"Rimini","IdRegioneResidenza":8,"IdRichiestaIovation":0,"BTAG":null,"HtmlPopupPostLogin":null,"ValidazioneContatti":1,"Brand":2,"DestinationUrl":null,"UtenteLTM":true,"PromoBenvenutoRetail":null,"PreferenzaInvioOTP":null,"DescPreferenzaInvioOTP":null,"FlgRicezioneOTP":null,"RecapitoPredefinitoIovation":null,"IdOrigineRegistrazione":0,"FlgRegistrazioneTipster":false,"IdTipoStatoTipster":null,"FlgCondivisioneAutomaticaTipster":null,"BS":true,"GruppoLamp":null,"ListIdTipoBS":[1],"CategoryCluster":[],"Vgh":false,"Message":"Success","ResultCode":0,"Skip":true,"MenuCdg":[{"Title":"Storico Conto","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Lista Giocate","DestinationUrl":"","IdDestination":6,"Children":null,"AzioniDaCompletare":0},{"Title":"Lista Movimenti","DestinationUrl":"","IdDestination":5,"Children":null,"AzioniDaCompletare":0},{"Title":"Storico Accessi","DestinationUrl":"","IdDestination":17,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":0},{"Title":"Profilo","DestinationUrl":null,"IdDestination":0,"Children":[{"Title":"Dati Personali","DestinationUrl":"","IdDestination":4,"Children":null,"AzioniDaCompletare":2},{"Title":"Sicurezza","DestinationUrl":"","IdDestination":9,"Children":null,"AzioniDaCompletare":0},{"Title":"Contratto di gioco","DestinationUrl":"","IdDestination":14,"Children":null,"AzioniDaCompletare":0},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"Privacy","DestinationUrl":"","IdDestination":12,"Children":null,"AzioniDaCompletare":0}],"AzioniDaCompletare":2},{"Title":"Gioco Responsabile","DestinationUrl":"","IdDestination":10,"Children":null,"AzioniDaCompletare":0},{"Title":"FAQ","DestinationUrl":"","IdDestination":62,"Children":null,"AzioniDaCompletare":0},{"Title":"Contatti","DestinationUrl":"","IdDestination":37,"Children":null,"AzioniDaCompletare":0}]}