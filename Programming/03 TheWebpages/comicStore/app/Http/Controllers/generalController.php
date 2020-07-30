<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\article;
use App\cart;
use App\discussion;
use App\article_comment;
use App\buy;
use DB;
use App\User;
use Illuminate\Support\Facades\Auth;

class generalController extends Controller
{
    
    public function showBuscar(){
        $query = new article();
        $articles = $query->hydrate(
            DB::select('call generalArticulo(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                14,
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
        $cat = $query2->hydrate(
            DB::select('call generalCategoria (?,?,?)', Array(
                3,
                null,
                null
            ))
        );

        return view ('buscar',['articles'=>$articles, 'cat'=>$cat]);
    }

    public function signinShow(){
    	return view ('sing_in');
    }
    public function sing_upShow(){
    	return view ('sing_up');
    }
    public function articuloShow(){
    	return view ('articulo');
    }
    public function articuloEditShow($id){
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

    	return view ('articuloEdit',['article'=>$article[0]]);
        //return view ('articuloEdit', ['article'=> $article]);
    }
    public function productShow($id){
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

        if(Auth::user()){
            $query2 = new article();
            $hasBought = $query->hydrate(
                DB::select('call generalArticulo(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                    12,
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
                    Auth::user()->id
                ))
            );
        }

        $query3 = new article_comment();
        $comments = $query->hydrate(
            DB::select('call generalComentario(?,?,?,?,?,?)', Array(
                6,
                null,
                null,
                null,
                null,
                $id,
            ))
        );

        $query4 = new article();
        $rating = $query4->hydrate(
            DB::select('call generalArticulo(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                13,
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
        
        if(Auth::user()){
            return view ('product',['article'=>$article[0], 'comments'=>$comments, 'hasBought'=>$hasBought, 'rating'=>$rating[0]]);
        }
        else{
            return view ('product',['article'=>$article[0], 'comments'=>$comments, 'rating'=>$rating[0]]);
        }
    }

    public function productShowCaca(){
        return view ('product');
    }

    public function showAddCart(Request $request){
        $query = new cart();
        $cart = $query->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                1,
                null,
                $request->user_id,
                $request->article_id,
                $request->unit,
                null
            ))
        );
        return redirect('loadCart/'.$request->user_id);
    }

    public function loadCart ($id){
        $query = new cart();
        $cart = $query->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                6,
                null,
                $id,
                null,
                null,
                null
            ))
        );
        //return $cart;
        return view ('cart',['cart'=>$cart]);
    }

    public function delCart ($id){
        $query = new cart();
        $cart = $query->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                4,
                $id,
                null,
                null,
                null,
                null
            ))
        );
        //return $cart;
        return redirect('loadCart/'.Auth::user()->id);
    }

    public function showDiscussAdmin(){
        $query = new discussion();
        $discuss = $query->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                9,
                null,
                null,
                null,
                null,
                null
                ))
            );

        $query2 = new discussion();
        $theBought = $query2->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                10,
                null,
                null,
                null,
                null,
                null
                ))
            );

        
            $query3 = new article();
            $cat = $query3->hydrate(
                DB::select('call generalCategoria (?,?,?)', Array(
                    3,
                    null,
                    null
                ))
            );
    

            return view ('adminDiscuss',['discuss'=>$discuss, 'cat'=>$cat, 'theBought'=>$theBought]);

    }

    public function showDiscuss($id){

        
        $query = new discussion();
        $dis = $query->hydrate(
            DB::select('call generalDiscussion (?,?,?,?,?,?,?)', Array(
                6,
                null,
                null,
                null,
                null,
                null,
                $id
                ))
            );
        $query2 = new cart();
        $cart = $query->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                2,
                $id,
                null,
                null,
                null,
                null
            ))
        );

        if ($cart->isEmpty()){
            $query2 = new buy();
            $cart = $query->hydrate(
            DB::select('call generalCompraArticulo (?,?,?,?,?,?,?,?,?,?,?)', Array(
                8,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                $id
                 ))
             );
        }

            return view ('discus',['dis'=>$dis, 'idcart'=>$id, 'idarticle'=>$cart[0]->article_id]);
    }

    public function createDiscuss(Request $request){

        DB::select('call generalDiscussion (?,?,?,?,?,?,?)', Array(
            1,
            null,
            null,
            $request->discuss,
            $request->user_id,
            $request->article_id,
            $request->cart_id
        ));

        $query = new discussion();
        $dis = $query->hydrate(
            DB::select('call generalDiscussion (?,?,?,?,?,?,?)', Array(
                6,
                null,
                null,
                null,
                null,
                null,
                $request->cart_id,
                ))
            );

            return view ('discus',['dis'=>$dis, 'idcart'=>$request->cart_id, 'idarticle'=>$request->article_id]);
    }

    public function profileShow($id){
        $query = new User();
        $user = $query->hydrate(
            DB::select('call generalUsuario (?,?,?,?,?,?,?,?,?,?,?)', Array(
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
            ))
        );


       if(Auth::guest() || Auth::user()->id != $id){
           $fQuery = new article();
            $myComics = $query->hydrate(
                DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                    9,
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
                    $id
                ))
            );
        }
        else{
            $fQuery = new article();
            $myComics = $query->hydrate(
                DB::select('call generalArticulo (?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                    7,
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
                    $id
                ))
            );

        }

        $bquery = new buy();
        $myBuys = $bquery->hydrate(
            DB::select('call generalCompraArticulo (?,?,?,?,?,?,?,?,?,?,?)', Array(
                6,
                null,
                $id,
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
        $rating = $query4->hydrate(
            DB::select('call generalArticulo(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', Array(
                13,
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

    	return view ('profile',['viewdUser'=>$user[0], 'myComics'=>$myComics, 'myBuys'=>$myBuys, 'rating'=>$rating[0]]);
    }

    public function individualBuy(Request $request){

        $query = new cart();
        $cart = $query->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                8,
                $request->cart_id,
                null,
                null,
                $request->newUnits,
                null
            ))
        );

        $query2 = new cart();
        $cart = $query2->hydrate(
            DB::select('call generalCarro (?,?,?,?,?,?)', Array(
                2,
                $request->cart_id,
                null,
                null,
                null,
                null
            ))
        );

        $query3 = new buy();
        $buy = $query3->hydrate(
            DB::select('call generalCompraArticulo (?,?,?,?,?,?,?,?,?,?,?)', Array(
                1,
                null,
                $cart[0]->user_id,
                $cart[0]->article_id,
                $request->radVal,
                null,
                null,
                $cart[0]->price,
                null,
                $cart[0]->units,
                $cart[0]->id
            ))
        );

        return redirect('loadCart/'.$cart[0]->user_id);
    }

    public function updateRates(Request $o)
    {
        
        DB::select('call generalCompraArticulo (?,?,?,?,?,?,?,?,?,?,?)', Array(
            7,
            null,
            Auth::user()->id,
            $o->article_id,
            null,
            null,
            null,
            null,
            $o->valorRating,
            null,
            null
        ));

        return back();
    }

    
}
