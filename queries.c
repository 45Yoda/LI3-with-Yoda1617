int artunicos (char* docname) {


	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(docname);
	int cont=0;
	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;
	cur = cur->next;
	for(cur ; cur ; cur = cur->next){
		if (!xmlStrcmp(cur->name,(const xmlChar *) "page"))
			cont++;
}
	return cont;
}

int arttotais (char* docname) {


	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr aux;

	doc = xmlParseFile(docname);
	int cont=0;
	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;
	cur = cur->next;
	for(cur ; cur ; cur = cur->next){
		aux=cur;
		if (!xmlStrcmp(cur->name,(const xmlChar *) "page")){
			for(cur = cur->xmlChildrenNode ; cur ; cur = cur->next){
				if ((!xmlStrcmp(cur->name, (const xmlChar *) "revision"))){
					cont++;
		}
}
}
		cur=aux->next;
}
	return cont;
}
