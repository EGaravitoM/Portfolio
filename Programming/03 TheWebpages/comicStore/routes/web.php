<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', 'ArticleController@index');

Route::get('profile/{id}','generalController@profileShow');
Route::get('sing_in','generalController@signinShow')->name('login');
Route::get('sing_up','generalController@sing_upShow');
Route::get('articulo','generalController@articuloShow')->middleware('auth');
Route::get('/editArticle/{id}','generalController@articuloEditShow')->middleware('auth');
Route::get('/deleteArticle/{id}','ArticleController@deleteArticle')->middleware('auth');
Route::get('/activate/{id}/{state}', 'ArticleController@activateArticle');
Route::post('/addCart', 'generalController@showAddCart' );
Route::get('/loadCart/{id}', 'generalController@loadCart');
Route::get('/delCart/{id}', 'generalController@delCart');
Route::get('/product', 'generalController@productShowCaca');
Route::get('/product/{id}', 'generalController@productShow');
Route::get('nosotros','generalController@nosotrosShow');
Route::get('logout', 'userContoller@logout');
Route::get('/follow/{id}', 'generalController@follow');
Route::get('/buscar', 'generalController@showBuscar' );
Route::get('/loadDiscuss/{id}', 'generalController@showDiscuss' );
Route::get('/loadDiscussAdmin', 'generalController@showDiscussAdmin' );
Route::post('/generateDiscution', 'generalController@createDiscuss' );
Route::post('/setPrice', 'ArticleController@setPrice' );
Route::post('/individualBuy', 'generalController@individualBuy');
Route::get('/updateRates', 'generalController@updateRates');

Route::get('/sendemail', function(){

    $data = array(
        'name' => "Flores Padron",
    );

    return "Éxito";
    

});
Route::get('/emailShow/{id}','generalController@emailShow' );

Route::post('/registro', 'userContoller@create');
Route::post('/login', 'userContoller@login');
Route::post('/articleMake', 'ArticleController@create');
Route::post('/generateComment/{id}', 'ComentsController@create');
Route::get('/index', 'IndexController@index');
