/** \file
 *  Game Develop
 *  2008-2013 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDCore/TinyXml/tinyxml.h"
#include "GDCore/PlatformDefinition/ExternalLayout.h"
#include "GDCore/PlatformDefinition/InitialInstancesContainer.h"
#include "GDCore/IDE/Dialogs/LayoutEditorCanvas/LayoutEditorCanvasOptions.h"

namespace gd
{

void ExternalLayout::LoadFromXml(const TiXmlElement * element)
{
    if ( element == NULL ) return;

    name = element->Attribute( "Name" ) != NULL ? element->Attribute( "Name" ) : "";
    instances.LoadFromXml(element->FirstChildElement("Instances"));
}

#if defined(GD_IDE_ONLY)
void ExternalLayout::SaveToXml(TiXmlElement * element) const
{
    if ( element == NULL ) return;

    element->SetAttribute("Name", name.c_str());

    TiXmlElement * instancesElement = new TiXmlElement("Instances");
    element->LinkEndChild(instancesElement);
    instances.SaveToXml(instancesElement);
}
#endif

}