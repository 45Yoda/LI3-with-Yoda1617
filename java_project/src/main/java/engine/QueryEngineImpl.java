package engine;

import li3.Interface;

import java.util.ArrayList;
import java.io.FileNotFoundException;

public class QueryEngineImpl implements Interface {

    private Registo reg;
    private CatArtigos cat;

    public void init() {
        this.reg = new Registo();
        this.cat= new CatArtigos();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
        CatArtigos cArt = reg.getCatArt();
        CatContrib cCont = reg.getCatCont();
        try{
            Parser.parseDoc(nsnaps, snaps_paths, cat, cCont);
        }
        catch(FileNotFoundException e){
            System.err.println("FileNotFoundException: " + e.getMessage());
        }

    }

    public long all_articles() {
        return 5;
    }

    public long unique_articles() {
        System.out.println(cat.getCatalogo().get((long)12));
        int i =cat.getCatalogo().size();
        System.out.println(i);
        return i;    
    }

    public long all_revisions() {
        int i = reg.getCatArt().getCatalogo().values().stream().mapToInt(a->a.getRevs().size()).sum();
        System.out.println(i);

        return i;
    }

    public ArrayList<Long> top_10_contributors() {

        return new ArrayList<Long>();
    }

    public String contributor_name(long contributor_id) {

        return " ";
    }

    public ArrayList<Long> top_20_largest_articles() {

        return new ArrayList<Long>();
    }

    public String article_title(long article_id) {

        return " ";
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {

        return new ArrayList<Long>();
    }

    public ArrayList<String> titles_with_prefix(String prefix) {

        return new ArrayList<String>();
    }

    public String article_timestamp(long article_id, long revision_id) {

        return " ";
    }

    public void clean() {

    }
}
