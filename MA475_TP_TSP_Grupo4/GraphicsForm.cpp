#include "GraphicsForm.h"

void MA475TPTSPGrupo4::GraphicsForm::update_node_table()
{
	MA475TPTSPGrupo4::MainForm^ main_form = static_cast<MA475TPTSPGrupo4::MainForm^>(parent);

	main_form->fill_node_table(interface->get_nodes());
}