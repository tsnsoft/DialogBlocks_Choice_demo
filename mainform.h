/////////////////////////////////////////////////////////////////////////////
// Name:        mainform.h
// Purpose:     Заголовочный файл для MainForm
// Author:      Sergey Talipov
// Created:     17/03/2025 14:32:03
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINFORM_H_
#define _MAINFORM_H_

#include <vector>
#include "wx/frame.h"
#include "wx/gbsizer.h"
#include "wx/stattext.h" // Для wxStaticText

/*!
 * Control identifiers
 */
#define ID_MAINFORM 10000
#define ID_STATIC_INGREDIENTS 10006
#define ID_CHOICE 10001
#define ID_LISTBOX 10002
#define ID_RADIOBOX 10003
#define ID_CHECKSALT 10005
#define ID_CHECKPIPER 10004
#define ID_BUTTON 10007

#define SYMBOL_MAINFORM_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_MAINFORM_TITLE wxT("Заказ салата")
#define SYMBOL_MAINFORM_IDNAME ID_MAINFORM
#define SYMBOL_MAINFORM_SIZE wxSize(300, 328)
#define SYMBOL_MAINFORM_POSITION wxDefaultPosition

 /*!
  * MainForm class declaration
  */
class MainForm : public wxFrame
{
	DECLARE_CLASS(MainForm)
	DECLARE_EVENT_TABLE()

public:
	MainForm();
	MainForm(wxWindow* parent, wxWindowID id = SYMBOL_MAINFORM_IDNAME, const wxString& caption = SYMBOL_MAINFORM_TITLE,
		const wxPoint& pos = SYMBOL_MAINFORM_POSITION, const wxSize& size = SYMBOL_MAINFORM_SIZE, long style = SYMBOL_MAINFORM_STYLE);

	bool Create(wxWindow* parent, wxWindowID id = SYMBOL_MAINFORM_IDNAME, const wxString& caption = SYMBOL_MAINFORM_TITLE,
		const wxPoint& pos = SYMBOL_MAINFORM_POSITION, const wxSize& size = SYMBOL_MAINFORM_SIZE, long style = SYMBOL_MAINFORM_STYLE);

	~MainForm();
	void Init();
	void CreateControls();
	void UpdateIngredientsDisplay(); // Обновление отображения ингредиентов

	void OnChoiceSelected(wxCommandEvent& event); // Обработчик события выбора элемента в списке выбора (Choice)
	void OnListboxSelected(wxCommandEvent& event); // Обработчик события выбора элемента в списке выбора (ListBox)
	void OnRadioboxSelected(wxCommandEvent& event); // Обработчик события выбора элемента в списке выбора (RadioBox)
	void OnChecksaltClick(wxCommandEvent& event); // Обработчик события изменения состояния флажка (CheckBox)
	void OnCheckpiperClick(wxCommandEvent& event); // Обработчик события изменения состояния флажка (CheckBox)
	void OnButtonClick(wxCommandEvent& event); // Обработчик события нажатия кнопки (Button)

	wxBitmap GetBitmapResource(const wxString& name);
	wxIcon GetIconResource(const wxString& name);

private:
	std::vector<wxString> ingredients; // Массив ингредиентов

	wxStaticText* ingredientsDisplay; // Отображение ингредиентов
	wxChoice* m_choice; // Список выбора (Choice)
	wxListBox* m_listbox; // Список выбора (ListBox)
	wxRadioBox* m_radiobox; // Список выбора (RadioBox)
	wxCheckBox* m_checkbox_s; // Флажок "Посолить"
	wxCheckBox* m_checkbox_p; // Флажок "Поперчить"
};

#endif // _MAINFORM_H_
