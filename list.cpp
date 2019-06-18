void listAll(const Domain * d, string path) {
    
    if (d->subdomains().size() == 0) {
        cout << path << endl;
        return;
    }
    
    for (vector<Domain *>::const_iterator it = d->subdomains().begin(); it != d->subdomains().end(); it++) {
        
        if (path != "") {
            listAll(*it, (*it)->label() + "." + path);
        }
        
        else {
            listAll(*it, (*it)->label() + path);
        }
    }
    
}

