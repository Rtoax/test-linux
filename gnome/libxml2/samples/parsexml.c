#include <stdio.h>
#include <libxml/parser.h>

int main(int argc, char* argv[])
{
	xmlDocPtr doc;
	xmlNodePtr curNode;
	xmlChar *szKey;
	char *szDocName;

	if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
	}

	szDocName = argv[1];
	doc = xmlReadFile(szDocName, "GB2312", XML_PARSE_RECOVER);
	if (NULL == doc) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return -1;
	}

	curNode = xmlDocGetRootElement(doc);

	if (NULL == curNode) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return -1;
	}

	if (xmlStrcmp(curNode->name, BAD_CAST "domain")) {
		fprintf(stderr,"document of the wrong type, root node != domain");
		xmlFreeDoc(doc);
		return -1;
	}

	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr = curNode;
	while (curNode != NULL) {
		if (!xmlStrcmp(curNode->name, BAD_CAST "name")) {
			szKey = xmlNodeGetContent(curNode);
			printf("name: %s\n", szKey);
			xmlFree(szKey);
		}

		if (xmlHasProp(curNode, BAD_CAST "attribute")) {
			propNodePtr = curNode;
		}

		curNode = curNode->next;
	}

	xmlAttrPtr attrPtr = propNodePtr->properties;
	while (attrPtr != NULL) {
		if (!xmlStrcmp(attrPtr->name, BAD_CAST "attribute")) {
			xmlChar* szAttr = xmlGetProp(propNodePtr, BAD_CAST "attribute");
			printf("get attribute = %s\n", szAttr);
			xmlFree(szAttr);
		}
		attrPtr = attrPtr->next;
	}

	xmlFreeDoc(doc);
	return 0;

}

