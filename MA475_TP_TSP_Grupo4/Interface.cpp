#include "Interface.h"

Interface::Interface()
{
	nodes = new vector<Point2D*>;
	routes = new vector<Line2D*>;
	texto = gcnew String(" ");

	Zona = Rectangle(170, 80, 600, 500);
	titulo = Rectangle(0, 0, 750, 80);
	x = 0; y = 0;
	R = 100, G = 50, B = 50;
	dR = 2, dG = 2, dB = 2;

	click = false;
}

Interface::~Interface()
{
	for (int i = 0; i < nodes->size(); ++i)
	{
		delete nodes->at(i);
	}

	delete nodes;

	for (int i = 0; i < routes->size(); ++i)
	{
		delete routes->at(i);
	}
	
	delete routes;
}

void Interface::draw(Graphics^ graphics)
{
	for (unsigned int i = 0; i < routes->size(); ++i)
	{
		(*routes)[i]->draw(graphics, roundf((*routes)[i]->distance()) + " KM");
	}

	for (unsigned int i = 0; i < nodes->size(); ++i)
	{
		(*nodes)[i]->draw(graphics, node_radius, (i + 1).ToString());
	}

	if (nodes->size() > 0)
	{
		init_node_pointer = new NodePointer2D((*nodes)[0]->x, (*nodes)[0]->y - 20.f);
		init_node_pointer->draw(graphics);
	}

	if (nodes->size() > 1)
	{
		finish_node_pointer = new NodePointer2D((*nodes)[nodes->size() - 1]->x, (*nodes)[nodes->size() - 1]->y - 20.f);
		finish_node_pointer->draw(graphics);
	}
}

void Interface::new_node(int x, int y)
{
	Point2D* node = new Point2D(x, y);
	nodes->push_back(node);
}

Line2D* Interface::new_route(int x1, int y1, int x2, int y2)
{
	Line2D* route = new Line2D(x1, y1, x2, y2);
	routes->push_back(route);

	return route;
}

void Interface::draw_routes()
{
	vector<int> row(nodes->size());
	vector<vector<int>> table(nodes->size(), row);

	for (int i = 0; i < nodes->size(); ++i)
	{
		if (i > 0)
		{
			for (int j = 0; j < i; j++)
			{
				Line2D* route = new_route((*nodes)[i]->x, (*nodes)[i]->y, (*nodes)[j]->x, (*nodes)[j]->y);

				table[i][j] = route->distance();
				table[j][i] = table[i][j];
			}
		}
	}

	node_table = new vector<vector<int>>(table);

	//String^ text = "";
	//for (int i = 0; i < table.size(); ++i)
	//{
	//	for (int j = 0; j < table[i].size(); ++j)
	//	{
	//		text += table[i][j] + " ";
	//	}

	//	text += "\n";
	//}

	//MessageBox::Show(text);

}

void Interface::drawer_iterator(Graphics^ graphics, int x, int y, bool is_click)
{
	if (following_node_on && node_to_follow != -1 && node_to_follow < nodes->size())
	{
		set_node_position(node_to_follow, x, y);
	}

	if (is_click)
	{
		draw_routes();
		node_to_follow = -1;
		following_node_on = false;
	}

	draw(graphics);
}

void Interface::new_node()
{
	new_node(0, 0);

	following_node_on = true;
	node_to_follow = nodes->size() - 1;
}

void Interface::delete_last_node()
{
	if (nodes->size() > 0)
	{
		nodes->erase(nodes->begin() + nodes->size() - 1);
		draw_routes();
	}
}

void Interface::solve_with_brute_force()
{
	solver->set_nodes(*node_table);
	solver->solve_brute_force(0);

	vector<vector<int>> result_routes = solver->get_optimal_routes_result();
	int result_route_cost = solver->get_optimal_routes_cost();

	MessageBox::Show("Costo de la ruta o rutas optima(s): " + result_route_cost);

	String^ result = "";

	for (int i = 0; i < result_routes.size(); ++i)
	{
		for (int node : result_routes[i])
		{
			result += node + " -> ";
		}

		result += "0\n";
	}

	MessageBox::Show(result);
}

void Interface::set_node_position(int node_index, float x, float y)
{
	if (node_index < nodes->size())
	{
		(*nodes)[node_index]->x = x;
		(*nodes)[node_index]->y = y;
	}
}
