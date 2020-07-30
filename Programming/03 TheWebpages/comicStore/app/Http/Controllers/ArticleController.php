<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Hash;
use App\article;
use App\User;
use DB;
use Illuminate\Support\Facades\Auth;

class ArticleController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        
        //$Articles = article::where('active_article', true)->get();
        //$new = article::where('active_article', true)->latest()->take(4)->get();
        //$rating = buys::where('article_id', $id)->avg("valoration")->orderBy('rating','desc')->take(4)->get();

        $query = new article();
        $articles = $query->hydrate(
            DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                18,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );

        $query2 = new article();
        $masCaros = $query2->hydrate(
            DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                16,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );
       
        $query3 = new article();
        $masBaratos = $query3->hydrate(
            DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                17,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );

        $query4 = new article();
        $votos = $query4->hydrate(
            DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                15,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );

        return view('index',['articles'=>$articles, 'masCaros'=>$masCaros, 'masBaratos'=>$masBaratos, 'votos'=>$votos]);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create(Request $o)
    {


        if($o->hasFile('comicImg1')){
            $file = $o->file('comicImg1')->getRealPath();
            $img1 = file_get_contents($file);
            $base64img1 = base64_encode($img1);
            $o->comicImg1 = $base64img1;
        }

        if($o->hasFile('comicImg2')){

            $file = $o->file('comicImg2')->getRealPath();
            $img2 = file_get_contents($file);
            $base64img2 = base64_encode($img2);
            $o->comicImg2 = $base64img2;
        }

        if($o->hasFile('comicImg3')){

            $file = $o->file('comicImg3')->getRealPath();
            $img3 = file_get_contents($file);
            $base64img3 = base64_encode($img3);
            $o->comicImg3 = $base64img3;
        }

        if($o->hasFile('comicvideo')){
            $file = $o->file('comicvideo');
            $videoideo_name = time().$file->getClientOriginalName();
            $file->move(public_path().'/images/', $videoideo_name);
            $o->comicvideo = $videoideo_name;
        }


        DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
            1,
            null,
            $o->name_article,
            $o->description_article,
            (float)$o->price,
            $o->units,
            false,
            false,
            null,
            $videoideo_name,
            $base64img1,
            $base64img2,
            $base64img3,
            Auth::user()->id
        ));

        $query = new article();
        $comic = $query->hydrate(
            DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                6,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );

        DB::select('call generalArticuloCategoria(?,?,?,?)', Array(
            1,
            null,
            $o->comicCategoria,
            $comic[0]->id
        ));

        
        return redirect('/product/'.$comic[0]->id);
    }

    public function setPrice(Request $request){
        DB::select('call generalCarro (?,?,?,?,?,?)', Array(
            7,
            $request->cart_id,
            null,
            null,
            null,
            (float)$request->fPrice
        ));

        return redirect('/loadDiscuss/'.$request->cart_id);
    }

    public function editArticle(Request $o, $id)
    {
        

        if($o->hasFile('comicImg1')){
            $file = $o->file('comicImg1')->getRealPath();
            $img1 = file_get_contents($file);
            $base64img1 = base64_encode($img1);
            $o->comicImg1 = $base64img1;
        }

        if($o->hasFile('comicImg2')){

            $file = $o->file('comicImg2')->getRealPath();
            $img2 = file_get_contents($file);
            $base64img2 = base64_encode($img2);
            $o->comicImg2 = $base64img2;
        }

        if($o->hasFile('comicImg3')){

            $file = $o->file('comicImg3')->getRealPath();
            $img3 = file_get_contents($file);
            $base64img3 = base64_encode($img3);
            $o->comicImg3 = $base64img3;
        }

        if($o->hasFile('comicvideo')){
            $file = $o->file('comicvideo');
            $videoideo_name = time().$file->getClientOriginalName();
            $file->move(public_path().'/images/', $videoideo_name);
            $o->comicvideo = $videoideo_name;
        }

        DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
            5,
            $id,
            $o->name_article,
            $o->description_article,
            (float)$o->price,
            $o->units,
            false,
            false,
            null,
            $videoideo_name,
            $base64img1,
            $base64img2,
            $base64img3,
            null
        ));

        $query = new article();
        $article = $query->hydrate(
            DB::select('call generalArticulo(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                2,
                $id,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );

        DB::select('call generalArticuloCategoria(?,?,?,?)', Array(
            5,
            null,
            $o->comicCategoria,
            $comic[0]->id
        ));

        return redirect('/profile/'.$article[0]->user_id);

    }

    public function activateArticle($id, $state){
        if($state){
            DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                10,
                $id,
                null,
                null,
                null,
                null,
                0,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ));
        }
        else{
            DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                10,
                $id,
                null,
                null,
                null,
                null,
                1,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ));
        }

        $query = new article();
        $article = $query->hydrate(
            DB::select('call generalArticulo(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                2,
                $id,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );

        return redirect('/profile/'.$article[0]->user_id);
    }

    public function deleteArticle($id)
    {

        $query = new article();
        $article = $query->hydrate(
            DB::select('call generalArticulo(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                2,
                $id,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null
            ))
        );

        DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
            4,
            $id,
            null,
            null,
            null,
            null,
            null,
            null,
            null,
            null,
            null,
            null,
            null,
            null
        ));

        return redirect('/profile/'.$article[0]->user_id);
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        //
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        //
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        //
    }

    public function addRating(Request $o, $id){

        $rating = Flowers_Rating::where('user_id', Auth::user()->id)->where('flower_id', $id)->first();

        if($rating){
            $rating->rating = $o->valorRating;
        }
        else {
            $rating = new Flowers_Rating();
            $rating->user_id = Auth::user()->id;
            $rating->flower_id = $id;
            $rating->rating = $o->valorRating;
        }

        $rating->save();

        $avgRating = Flowers_Rating::where('flower_id', $id)->avg("rating");
        $flor = Flower::find($id);
        $flor->rating = $avgRating;
        $flor->save();

        return back();

    }

}
