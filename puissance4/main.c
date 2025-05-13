#include <stdio.h>	// printf
#include <stdlib.h>	// atoi
#include <string.h>	// memset

typedef struct Game
{
	int **tableau;
	int	tour;
	int largeur;
	int hauteur;
}	Game;

Game *CreerTableau(int largeur, int hauteur)
{
	Game *game;
	game = malloc(sizeof(Game));
	game->largeur = largeur;
	game->hauteur = hauteur;
	game->tour	= 0;
	game->tableau = malloc(sizeof(int *) * largeur);
	memset(game->tableau, 0, sizeof(int *) * largeur);
	for (int i = 0; i < largeur; i++)
	{
		game->tableau[i] = malloc(sizeof(int) * hauteur);
		memset(game->tableau[i], 0, sizeof(int) * hauteur);
	}
	return  game;
}

void DessinerTableau(Game *game)
{
	for (int y = 0; y < game->hauteur; y++)
	{
		for (int x = 0; x < game->largeur; x++)
		{
			int val = game->tableau[x][y];
			if (val == 0)
				printf(". ");
			else if (val == 1)
				printf("X "); else
				printf("O ");
		}
		printf("\n");
	}
	printf("\n");
}




int	CheckHorizontalVertical(Game *game, int alignement)
{
	for (int y = 0; y < game->hauteur; y++)
	{
		for (int x = 0; x < game->largeur; x++)
		{
			int val = game->tableau[x][y];
			if (val == 0)
				continue;

			// Horizontal
			if (x + alignement <= game->largeur)
			{
				int win = 1;
				for (int i = 1; i < alignement; i++)
					if (game->tableau[x + i][y] != val)
						win = 0;
				if (win)
					return val;
			}

			// Vertical
			if (y + alignement <= game->hauteur)
			{
				int win = 1;
				for (int i = 1; i < alignement; i++)
					if (game->tableau[x][y + i] != val)
						win = 0;
				if (win)
					return val;
			}
		}
	}
	return 0;
}


int	CheckDiagonals(Game *game, int alignement)
{
	for (int y = 0; y < game->hauteur; y++)
	{
		for (int x = 0; x < game->largeur; x++)
		{
			int val = game->tableau[x][y];
			if (val == 0)
				continue;

			// Diagonale
			if (x + alignement <= game->largeur && y + alignement <= game->hauteur)
			{
				int win = 1;
				for (int i = 1; i < alignement; i++)
					if (game->tableau[x + i][y + i] != val)
						win = 0;
				if (win)
					return val;
			}

			// Anti-diagonale
			if (x - alignement + 1 >= 0 && y + alignement <= game->hauteur)
			{
				int win = 1;
				for (int i = 1; i < alignement; i++)
					if (game->tableau[x - i][y + i] != val)
						win = 0;
				if (win)
					return val;
			}
		}
	}
	return 0;
}

int	CheckVictoire(Game *game, int alignement)
{
	int winner = CheckHorizontalVertical(game, alignement);
	if (winner)
		return winner;
	return CheckDiagonals(game, alignement);
}


int	PlacerJeton(Game *game, int colonne, int joueur)
{
	if (colonne < 0 || colonne >= game->largeur)
		return 0;

	for (int y = game->hauteur - 1; y >= 0; y--)
	{
		if (game->tableau[colonne][y] == 0)
		{
			game->tableau[colonne][y] = joueur;
			game->tour++;
			return 1;
		}
	}
	return 0;
}


// ac est le nombre d'arguments du programme
// av est la liste d'argumetns du programme
int main(int ac, char **av)
{
	if (ac != 4)
	{
		printf("Usage: %s <hauteur> <largeur> <taille>\n", av[0]);
		return 1;
	}

	int hauteur = atoi(av[1]);
	int largeur = atoi(av[2]);
	int tailleCheck = atoi(av[3]);

	if (hauteur <= 0 || largeur <= 0 || tailleCheck <= 0)
	{
		printf("Paramètres invalides.\n");
		return 1;
	}

	Game *game = CreerTableau(largeur, hauteur);

	while (1)
	{
		DessinerTableau(game);
		int joueur = (game->tour % 2) + 1;
		printf("Joueur %d, entrez une colonne (0 à %d) : ", joueur, largeur - 1);

		int colonne;
		if (scanf("%d", &colonne) != 1)
		{
			printf("Entrée invalide.\n");
			break;
		}

		if (!PlacerJeton(game, colonne, joueur))
		{
			printf("Colonne pleine ou invalide, réessayez.\n");
			continue;
		}

		int winner = CheckVictoire(game, tailleCheck);
		if (winner)
		{
			DessinerTableau(game);
			printf("Le joueur %d a gagné !\n", winner);
			break;
		}

		if (game->tour == hauteur * largeur)
		{
			DessinerTableau(game);
			printf("Match nul !\n");
			break;
		}
	}
	return 0;
}
