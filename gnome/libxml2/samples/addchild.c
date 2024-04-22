#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int xmlAddChildFromString(xmlNodePtr parent, xmlChar *newNodeStr)
{
	xmlChar *newNodeStrWrapped = calloc(strlen(newNodeStr) + 10, 1);
	if (!newNodeStrWrapped)
		return 0;

	strcat(newNodeStrWrapped, BAD_CAST "<a>");
	strcat(newNodeStrWrapped, BAD_CAST newNodeStr);
	strcat(newNodeStrWrapped, BAD_CAST "</a>");
	xmlDocPtr newDoc = xmlReadMemory(newNodeStrWrapped,
					strlen(newNodeStrWrapped), NULL, NULL, 0);
	free(newNodeStrWrapped);
	if (!newDoc)
		return 0;
	xmlNodePtr newNode = xmlDocCopyNode(xmlDocGetRootElement(newDoc),
				parent->doc, 1);
	xmlFreeDoc(newDoc);

	if (!newNode)
		return 0;

	xmlNodePtr addedNode = xmlAddChildList(parent, newNode->children);
	if (!addedNode) {
		xmlFreeNode(newNode);
		return 0;
	}
	return 1;
}

int main(int argc, char **argv)
{
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr root = xmlNewNode(NULL, BAD_CAST "root");

	xmlDocSetRootElement(doc, root);

	xmlAddChildFromString(root,
			BAD_CAST "<street>Park Street</street><city>kolkata</city>");

	xmlDocDump(stdout, doc);

	xmlFreeDoc(doc);
	return(0);
}

