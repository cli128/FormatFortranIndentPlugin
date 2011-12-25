/***************************************************************
 * Name:      Format_Fortran_Indent_Plugin.h
 * Purpose:   declaration of Code::Blocks plugin Format_Fortran_Indent_Plugin
 * Author:    YWX (wxFortranIndent@163.com) or wxFortranIndent (wxFortranIndent@gmail.com)
 * Created:   2011-12-22
 * Copyright: (c) 2011 YWX <wxFortranIndent@163.com>
 * License:   GNU General Public License, version 3
 **************************************************************/

#ifndef FORMAT_FORTRAN_INDENT_PLUGIN_H_INCLUDED
#define FORMAT_FORTRAN_INDENT_PLUGIN_H_INCLUDED

// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <cbplugin.h> // for "class cbToolPlugin"

# include <wx/hashmap.h>
# include <wx/regex.h>

#define Max_Line_Char 512

class Format_Fortran_Indent_Plugin : public cbToolPlugin
{
public:
    /** Constructor. */
    Format_Fortran_Indent_Plugin();
    /** Destructor. */
    virtual ~Format_Fortran_Indent_Plugin();

    /** Invoke configuration dialog. */
    virtual int Configure();

    /** Return the plugin's configuration priority.
      * This is a number (default is 50) that is used to sort plugins
      * in configuration dialogs. Lower numbers mean the plugin's
      * configuration is put higher in the list.
      */
    virtual int GetConfigurationPriority() const
    {
        return 50;
    }

    /** Return the configuration group for this plugin. Default is cgUnknown.
      * Notice that you can logically OR more than one configuration groups,
      * so you could set it, for example, as "cgCompiler | cgContribPlugin".
      */
    virtual int GetConfigurationGroup() const
    {
        return cgUnknown;
    }

    /** Return plugin's configuration panel.
      * @param parent The parent window.
      * @return A pointer to the plugin's cbConfigurationPanel. It is deleted by the caller.
      */
    virtual cbConfigurationPanel* GetConfigurationPanel(wxWindow* parent)
    {
        return 0;
    }

    /** Return plugin's configuration panel for projects.
      * The panel returned from this function will be added in the project's
      * configuration dialog.
      * @param parent The parent window.
      * @param project The project that is being edited.
      * @return A pointer to the plugin's cbConfigurationPanel. It is deleted by the caller.
      */
    virtual cbConfigurationPanel* GetProjectConfigurationPanel(wxWindow* parent, cbProject* project)
    {
        return 0;
    }

    /** This method is called by Code::Blocks core modules (EditorManager,
      * ProjectManager etc) and is used by the plugin to add any menu
      * items it needs in the module's popup menu. For example, when
      * the user right-clicks on a project file in the project tree,
      * ProjectManager prepares a popup menu to display with context
      * sensitive options for that file. Before it displays this popup
      * menu, it asks all attached plugins (by asking PluginManager to call
      * this method), if they need to add any entries
      * in that menu. This method is called.\n
      * If the plugin does not need to add items in the menu,
      * just do nothing ;)
      * @param type the module that's preparing a popup menu
      * @param menu pointer to the popup menu
      * @param data pointer to FileTreeData object (to access/modify the file tree)
      */
    void BuildModuleMenu( const ModuleType type, wxMenu* menu, const FileTreeData* data = 0 );

    /** @brief Execute the plugin.
      *
      * This is the only function needed by a cbToolPlugin.
      * This will be called when the user selects the plugin from the "Plugins"
      * menu.
      */
    virtual int Execute();

    void OnFormatActiveFile( wxCommandEvent& event );
    void OnFormatProject( wxCommandEvent& event );
    void FormatFile( const wxString &filename );
    bool FormatEditor( cbEditor *ed );

protected:
    /** Any descendent plugin should override this virtual method and
      * perform any necessary initialization. This method is called by
      * Code::Blocks (PluginManager actually) when the plugin has been
      * loaded and should attach in Code::Blocks. When Code::Blocks
      * starts up, it finds and <em>loads</em> all plugins but <em>does
      * not</em> activate (attaches) them. It then activates all plugins
      * that the user has selected to be activated on start-up.\n
      * This means that a plugin might be loaded but <b>not</b> activated...\n
      * Think of this method as the actual constructor...
      */
    virtual void OnAttach();

    /** Any descendent plugin should override this virtual method and
      * perform any necessary de-initialization. This method is called by
      * Code::Blocks (PluginManager actually) when the plugin has been
      * loaded, attached and should de-attach from Code::Blocks.\n
      * Think of this method as the actual destructor...
      * @param appShutDown If true, the application is shutting down. In this
      *         case *don't* use Manager::Get()->Get...() functions or the
      *         behaviour is undefined...
      */
    virtual void OnRelease(bool appShutDown);

    /// pre
	WX_DECLARE_STRING_HASH_MAP( wxRegEx *, MyFortranRegEx );
	MyFortranRegEx myFortranRegEx;

	void myCreateFortranRegEx( );
	void getFortranIndentLine( MyFortranRegEx pFortranRegEx, const wxString & src, int & indentNum, bool & isCur, bool & isCaseBegin );

    DECLARE_EVENT_TABLE()
};

#endif // FORMAT_FORTRAN_INDENT_PLUGIN_H_INCLUDED
