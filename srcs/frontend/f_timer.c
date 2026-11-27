// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   time.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
// /*   Updated: 2026/11/22 12:38:29 by alerusso42       ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/frontend.h"

//SECTION - defines

#define TIMERS_TIME	\
(const int [])\
{\
	[TIM_FPS] = FRAME_TIME, \
	[TIM_SECOND] = 1000e3, \
	[TIM_END] = 2000e3, \
	[TIM_RENDER] = 30e3, \
	[TIM_TEST] = 5000e3, \
	[TIM_NUM] = 0 \
}

void	F_timeHandler_fps(t_F *front);
void	F_timeHandler_second(t_F *front);
void	F_timeHandler_endCheck(t_F *front);
void	F_timeHandler_firstRender(t_F *front);
void	F_timeHandler_test(t_F *front);

#define TIMERS_HANDLER	\
(void (*[])(t_F*))\
{\
	[TIM_FPS] = F_timeHandler_fps, \
	[TIM_SECOND] = F_timeHandler_second, \
	[TIM_END] = F_timeHandler_endCheck, \
	[TIM_RENDER] = F_timeHandler_firstRender, \
	[TIM_TEST] = F_timeHandler_test, \
	[TIM_NUM] = NULL \
}

//SECTION - init

void	F_timeStart(t_F *front)
{
	for (int i = 0; i != TIM_NUM; i++)
	{
		timer_init(&front->timers[i], TIMERS_TIME[i], \
		(void *)TIMERS_HANDLER[i], front);
	}
	front->timers[TIM_FPS].reverse_activation = true;
}

//SECTION - handlers implementation

void	F_timeHandler_fps(t_F *front)
{
	t_timer	*timer;

	timer = &front->timers[TIM_FPS];
	SDL_Delay(((double)timer->_curr / 1000) + 0.5);
	timer_reset(timer);
	front->fps_count++;
}

void	F_timeHandler_second(t_F *front)
{
	front->fps = front->fps_count;
	front->fps_count = 0;
	// debug_log_int(front->proc, "$YFPS$Z: %d", front->fps);
}

void	F_timeHandler_endCheck(t_F *front)
{
	bool	alone;

	sem_wait(&front->proc->shared->s_gen);
	alone = front->proc->shared->n_client <= 1; 
	sem_post(&front->proc->shared->s_gen);
	if (alone)
		front->power_on = false;
}

//one time handler to delay rendering
void	F_timeHandler_firstRender(t_F *front)
{
	F_render_reset(front);
	front->timers[TIM_RENDER].handler = NULL;
}

void	F_timeHandler_test(t_F *front)
{
	(void)front;
	// debug_log(front->proc, "test");
}
