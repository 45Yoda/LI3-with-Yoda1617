package engine;

import li3.Interface;

import java.util.List;
import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.util.stream.Collectors;
import java.lang.String;
import java.util.Collections;

public class QueryEngineImpl implements Interface {

    private CatArtigos cCat;
    private CatContrib cCont;

    public void init() {
        this.cCat= new CatArtigos();
        this.cCont = new CatContrib();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
        try{
            Parser.parseDoc(nsnaps, snaps_paths, this.cCat, this.cCont);
        }
        catch(FileNotFoundException e){
            System.err.println("FileNotFoundException: " + e.getMessage());
        }

    }

    public long all_articles() {
        return this.cCat.getCatalogo().values().stream().mapToInt(a->a.getFlag()).sum();
    }

    public long unique_articles() {
        return this.cCat.getCatalogo().size();
    }

    public long all_revisions() {
        return this.cCat.getCatalogo().values().stream().mapToInt(a->a.getRevs().size()).sum();

    }

    public ArrayList<Long> top_10_contributors() {
        ArrayList<Long> lista;
        lista = cCont.getCatalogo().values().stream().sorted(new ComparatorContribuicoes()).limit(10).map(c->(c.getId())).collect(Collectors.toCollection(ArrayList :: new));
        return lista;
    }

    public String contributor_name(long contributor_id) {

        try {
            return this.cCont.getCatalogo().get(contributor_id).getUsername();
             }
        catch(NullPointerException e){
            System.err.println(e.getMessage());
            return "Contribuidor nao existe";
    }
    }


    public ArrayList<Long> top_20_largest_articles() {
        ArrayList<Long> lista;
        lista = cCat.getCatalogo().values().stream().sorted(new ComparatorBytes()).limit(20).map(c->(c.getId())).collect(Collectors.toCollection(ArrayList :: new));
        return lista;
    }

    public String article_title(long article_id) {
        try {

        return this.cCat.getCatalogo().get(article_id).getTitulo();
        
        }
        catch(NullPointerException e){
            System.err.println(e.getMessage());
            return "Artigo nao existe";
    }    
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {

        return cCat.getCatalogo().values().stream().sorted(new ComparatorWords()).limit(n).map(c->(c.getId())).collect(Collectors.toCollection(ArrayList :: new));
    }

    public ArrayList<String> titles_with_prefix(String prefix) {
        try {
        ArrayList<String> lista = cCat.getCatalogo().values().stream().filter(f->(f.getTitulo()).contains(prefix)).map(a->a.getTitulo()).collect(Collectors.toCollection(ArrayList :: new));
        Collections.sort(lista);
        return lista;
        }
        catch(NullPointerException e){
            System.err.println(e.getMessage());
            return null;
    }
}

    public String article_timestamp(long article_id, long revision_id) {

        try {
         return this.cCat.getCatalogo().get(article_id).getRevs().get(revision_id).getTimestamp();
        }
        catch(NullPointerException e){
            System.err.println(e.getMessage());
            return "Artigo ou revisao nao existe";
    }
}

    public void clean() {
        cCat.clean();
        cCont.clean();
    }
}
