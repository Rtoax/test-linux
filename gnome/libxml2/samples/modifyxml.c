#include <stdio.h>
#include <libxml/parser.h>

int main(int argc, char* argv[])
{
	xmlDocPtr doc;
	xmlNodePtr curNode;

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

	curNode = curNode->children;
	while (NULL != curNode) {
		/* Delete Node1 */
		if (!xmlStrcmp(curNode->name, BAD_CAST "newNode1")) {
			xmlNodePtr tempNode;
			tempNode = curNode->next;
			xmlUnlinkNode(curNode);
			xmlFreeNode(curNode);
			curNode = tempNode;
			continue;
		}

		if (!xmlStrcmp(curNode->name, BAD_CAST "node2")) {
			xmlSetProp(curNode,BAD_CAST "attribute", BAD_CAST "no");
		}
		if (!xmlStrcmp(curNode->name, BAD_CAST "newNode2")) {
			xmlNodeSetContent(curNode, BAD_CAST "content changed");
		}
		if (!xmlStrcmp(curNode->name, BAD_CAST "newNode3")) {
			xmlNewProp(curNode, BAD_CAST "newAttr", BAD_CAST "YES");
		}

		if (!xmlStrcmp(curNode->name, BAD_CAST "son")) {
			xmlNewTextChild(curNode, NULL, BAD_CAST "newGrandSon", BAD_CAST "new content");
		}

		curNode = curNode->next;
	}

	int nRel = xmlSaveFile("tmp-changed.xml", doc);
	if (nRel != -1) {
		printf("Create new xml, write %d Bytes\n", nRel);
	}
	xmlFreeDoc(doc);
	return 0;
}

