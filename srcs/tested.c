double radians_to_degrees(double radians)
{
	return ((radians * 180) / PI);
}

double degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

double calculate_phi(double x, double y)
{
	double phi = atan2(y, x);

	if (phi < 0) {
		return radians_to_degrees(phi + 2 * PI);
	} else {
		return radians_to_degrees(phi);
	}
}

double calculate_distance_to_wall(t_data *data)
{
	int			distance_to_wall;
	double		angle = data->player->angle;
	double phi1 = calculate_phi(data->map->width - data->player->x, data->player->y);
	double phi2 = calculate_phi(data->player->y, -(data->player->x));
	double phi3 = calculate_phi(-data->player->x, -(data->map->height - data->player->y));
	double phi4 = calculate_phi(-(data->map->height - data->player->y), data->map->width - data->player->x);

	printf("%0.2f\n%0.2f\n%0.2f\n%0.2f\n", phi1, phi2, phi3, phi4);
	while (data->player->angle >= 360)
		data->player->angle -= 360;
	if (angle == 90, angle == 135, angle == 270)
		angle = 0;
	else
	{
		while (angle > 45)
			angle -= 45;
	}
	if (data->player->angle >= phi1	&& data->player->angle <= phi2)
	{
		distance_to_wall = data->player->y - SIZE;
		printf("oben\n");
	}
	else if (data->player->angle > phi2 && data->player->angle < phi3)
	{
		distance_to_wall = data->player->x - SIZE;
		printf("links\n");
	}
	else if (data->player->angle >= phi3 && data->player->angle <= phi4)
	{
		distance_to_wall = data->map->height - data->player->y - SIZE;
		printf("unten\n");
	}
	else
	{
		distance_to_wall = data->map->width - data->player->x - SIZE;
		printf("rechts\n");
	}
	printf("%d  %d\n", data->player->y, -(data->player->x));
	return (distance_to_wall / cos(degrees_to_radians(angle)));
}
