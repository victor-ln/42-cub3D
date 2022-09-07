/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:29:02 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/06 21:32:16 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

typedef enum e_menu_screen{
	SELECTION_MENU,
	OPTIONS_MENU
}	t_menu_screen;

enum e_menu_selection{
	RESUME,
	OPTIONS,
	EXIT
};

enum e_menu_options{
	MOUSE_SPEED,
	RESOLUTION,
	MAIN_MENU,
	MOUSE_SPEED_SELECTED_1,
	MOUSE_SPEED_SELECTED_2,
	MOUSE_SPEED_SELECTED_3,
	MOUSE_SPEED_SELECTED_4,
	RESOLUTION_SELECTED_1,
	RESOLUTION_SELECTED_2,
	RESOLUTION_SELECTED_3,
	RESOLUTION_SELECTED_4
};

typedef enum e_mouse_speed{
	SLOW,
	MEDIUM,
	FAST,
	FASTEST
}	t_mouse_speed;

typedef enum e_resolution{
	LIT,
	MID,
	BIG,
	FULL
}	t_resolution;

typedef struct s_menu
{
	int						menu_index;
	t_resolution			resolution;
	t_mouse_speed			mouse_speed;
	t_menu_screen			menu_screen;
	bool					is_selected;
}	t_menu;

#endif
