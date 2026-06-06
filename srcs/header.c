/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:57:54 by matnusko          #+#    #+#             */
/*   Updated: 2026/06/05 19:14:05 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* ========================================================================== */
/*                           COLOR DEFINITIONS                                */
/* ========================================================================== */

#define RED_BOLD        "\033[1;31m"
#define GREEN_BOLD      "\033[1;32m"
#define YELLOW_BOLD     "\033[1;33m"
#define BLUE_BOLD       "\033[1;34m"
#define MAGENTA_BOLD    "\033[1;35m"
#define CYAN_BOLD       "\033[1;36m"
#define WHITE_BOLD      "\033[1;37m"
#define RESET           "\033[0m"

#define DELAY_TIME      30000
#define DELAY_DOT       1000

/* ========================================================================== */
/*                           UTILITY FUNCTIONS                                */
/* ========================================================================== */

/**
 * delay - Creates a small delay using busy-wait loop
 * @iterations: Number of iterations for the delay
 *
 * Used for visual effects and timing between outputs.
 * Performance depends on system CPU speed.
 *
 * Return: void
 */
void	delay(long iterations)
{
	long	i;

	i = 0;
	while (i < iterations)
		i++;
}

/* ========================================================================== */
/*                              ASCII ART                                     */
/* ========================================================================== */

/**
 * display_title - Displays the Cub3D title and info
 *
 * Shows a simple ASCII art title with project information
 * using only printf for output.
 *
 * Return: void
 */
void	display_title(void)
{
	printf("\n");
	printf(RED_BOLD);
	printf("╔═════════════════════════════════════════════════════╗\n");
	printf("║                                                     ║\n");
	printf(CYAN_BOLD);
	printf("║       ██████╗██╗   ██╗██████╗ ██████╗ ██████╗       ║\n");
	printf("║      ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗      ║\n");
	printf("║      ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║      ║\n");
	printf("║      ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║      ║\n");
	printf("║      ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝      ║\n");
	printf("║       ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝       ║\n");
	printf(RED_BOLD);
	printf("║                                                     ║\n");
	printf("║          My first RayCaster with MLX42              ║\n");
	printf("║             42 School Project                       ║\n");
	printf("║                              by matnusko & nkuydin  ║\n");
	printf("╚═════════════════════════════════════════════════════╝\n");
	printf(RESET);
}

/**
 * display_controls - Shows all game control keys
 *
 * Displays movement, rotation, and exit controls in a
 * simple formatted layout using printf.
 *
 * Return: void
 */
void	display_controls(void)
{
	printf("\n");
	printf(YELLOW_BOLD);
	printf("╔═══════════════════════════════════════════════════════╗\n");
	printf("║                    CONTROL KEYS                       ║\n");
	printf("╠═══════════════════════════════════════════════════════╣\n");
	printf(GREEN_BOLD);
	printf("║  MOVEMENT:                                            ║\n");
	printf(RESET);
	printf("║    W - Move Forward       S - Move Backward           ║\n");
	printf("║    A - Strafe Left        D - Strafe Right            ║\n");
	printf(MAGENTA_BOLD);
	printf("║  VIEW ROTATION:                                       ║\n");
	printf(RESET);
	printf("║    ← - Look Left          → - Look Right              ║\n");
	printf(RED_BOLD);
	printf("║  EXIT:                                                ║\n");
	printf(RESET);
	printf("║    ESC - Close Window     Red X - Close Window        ║\n");
	printf(YELLOW_BOLD);
	printf("╚═══════════════════════════════════════════════════════╝\n");
	printf(RESET);
}

/* ========================================================================== */
/*                          LOADING ANIMATION                                 */
/* ========================================================================== */

/**
 * display_loading - Shows a simple loading message
 *
 * Displays initialization progress using only printf.
 * Simple and effective without complex animations.
 *
 * Return: void
 */
void	display_loading(void)
{
	printf("\n");
	printf("  %-40s", "Initializing Game Engine");
	printf(GREEN_BOLD "✓" RESET);
	printf("\n\n");
}

/* ========================================================================== */
/*                            MAIN HEADER FUNCTION                            */
/* ========================================================================== */

/**
 * header - Main function to display welcome screen
 *
 * Orchestrates the display sequence:
 * - Display title/logo
 * - Show loading message
 * - Display control keys
 *
 * Called at program startup before main game loop.
 *
 * Return: void
 */
void	header(void)
{
	display_title();
	display_loading();
	display_controls();
	printf("\n");
}
