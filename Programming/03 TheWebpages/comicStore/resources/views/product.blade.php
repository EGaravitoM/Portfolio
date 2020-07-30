<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Producto</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">

    <link rel="stylesheet" href="../css/reset.css">
    <link rel="stylesheet" href="../css/product.css">
    <link rel="stylesheet" href="../css/navbar.css">

   <script src="../js/starrr.js"></script>
    

    
</head>
<body>

<ul class="GNB fixed-top">
          <li class="GNB_E inicionav"></li>
          <li class="GNB_E"><a class="" href="/"><img class="logo" src="https://bit.ly/2u7pIbu"></a></li>
          <li class="GNB_E"><a class="GNB_A" href="/">Inicio</a></li>
          @if (Auth::user())
          @if(Auth::user()->rol == 1)
          <li class="GNB_E"><a class="GNB_A" href="/articulo">Crear Comic</a></li>
          @endif
          @endif
          <li class="GNB_E"><a class="GNB_A" href="/buscar">Buscar</a></li>
          <li class="GNB_E SI finnav"></li>

          @if (Auth::guest())
          <li class="GNB_E SI"><a class="GNB_A" href="/sing_in">Ingresar</a></li>
          @else
          <li class="GNB_E SI"><a class="GNB_A" href="/logout" >Salir</a></li>
          <li class="GNB_E SI"><a class="GNB_A" href="/profile/{{Auth::user()->id}}" >{{Auth::user()->name}}</a></li>
          <li class="GNB_E SI"><img id="uimg"  src="data:image/jpeg;base64, {{Auth::user()->user_avatar}}" alt=""></li>
         
            <li class="GNB_E SI"><a class="GNB_A" href="/loadCart/{{Auth::user()->id}}">Carrito</a></li>
          
          @endif
        </ul>

    
        
                <br>

        <h1 id="ndp" value="" >{{$article->name_article}}</h1>
        @if (Auth::user())
        @if(Auth::user()->rol == 1)
        <a class="btn commonB" href="/loadDiscussAdmin">Discusion</a>
        @endif
        @endif
        <div id="imgs">
            <div id="imgMain" class="container">
                <img id="main" src="data:image/jpeg;base64, {{$article->img1}}" alt="Imagen no Encontrada">
            </div>
            <div id="ImgMuestra" class="container">
                <img id="top" src="data:image/jpeg;base64, {{$article->img2}}" alt="img2 n/e">
            </div>
            <div id="ImgMuestra2" class="container">
                <img id="top" src="data:image/jpeg;base64, {{$article->img3}}" alt="img3 n/e">
            </div>
        </div>

        
        <div class="descpres">
            <div class="descripcion">
                <p id="info" class="des cripcion" value="" >{{$article->description_article}}</p>   
            </div>
            <div id="percio_unidades">
                Precio: <b><span value="">${{$article->price}}</span></b><br>
                Unidades: <b><span value="" >{{$article->units}}</span></b><br>
                Categoría: <b><span>{{$article->name_category}}</span></b>
                <div id="casaEstrellas">
                Rating: <span id="Estrellas" value="" ><b>{{$rating->rating}}</b></span> 
                    
                    @if (!Auth::guest())
                    @if($hasBought[0]->answer)
                    <form id="rateo" method="get" action="/updateRates">
                        @csrf
                        <button class="estrellita star_b" value="1" id="primero"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="2" id="segundo"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="3" id="tercero"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="4" id="cuarto"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="5" id="quinto"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <input type="hidden" id="goodStar" name="valorRating" value="">
                        <input type="hidden" id="idcar" name="article_id" value="{{$article->id}}">

                        <script>

                            $(document).ready(function(){
                                $('.estrellita').on('mouseenter', function(){
                                    var index = $(this).index();
                                    var tmpindex = 0;
                                    $('.estrellita').each(function(sindex){
                                        if(sindex < index){
                                            $(this).addClass('star_y');
                                            $(this).removeClass('star_b');
                                        }
                                        else{
                                            $(this).addClass('star_b');
                                            $(this).removeClass('star_y');
                                        }
                                    });
                                });

                                $(".estrellita").click(function(){
                                    $("#goodStar").val($(this).val());
                                    $("#rateo").submit();
                                });
                            });

                        </script>
                       <!-- <label for="#segundo"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="4" id="segundo">
                        <label for="#tercero"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="3" id="tercero">
                        <label for="#cuarto"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="2" id="cuarto">
                        <label for="#quinto"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="1" id="quinto"> -->
                    </form>
                    @endif
                    @endif
                    
                    <br>
                </div>
            </div>
        </div>
        <div class="compra_fav container">

            <form method="post" action="/addCart">
            @csrf
                <div class="container form-group" id="amount">
                    <label for="#units">Selecciona las que Quieras</label>
                    <input type="number" name="unit" class="form-control"  min="1" id="units" required>
                    <input type="hidden" name="article_id" value="{{$article->id}}">
                    @if(Auth::user())
                    <input type="hidden" name="user_id" value="{{Auth::user()->id}}">
                    @endif
                    <br>
                    <input type="hidden" name="creatorId" value="" required>
                    <input type="hidden" name="articleId" value="" required>
                    @if (Auth::guest())
                        <a id="ATC" class="btn commonB" href="/sing_in">Añadir al Carrito</a>
                    @else
                        <input type="submit" id="ATC" class="btn commonB" value="Añadir al Carrito">
                    @endif
                    
                </div>
            </form>

        </div>

    <div class="video container">
        <video style="align-self: center" src="../images/{{$article->video}}" controls></video>
        </div>
        
    
   

    <form method="post" action="/generateComment/{{$article->id}}">
        @csrf
        <div class="container form-group comentgroup">
            @if (Auth::guest())
                <textarea placeholder="Añade un comentario..." name="coments" id="cbox" cols="150" rows="3"></textarea>
                <a id="bc2" class="btn commonB" href="/sing_in">Comentar</a>
            @else
                
                    <textarea placeholder="Añade un comentario..." name="coments" id="cbox" cols="150" rows="3" required></textarea>
                
                @if($hasBought[0]->answer)
                    <input type="submit" id="bc2" class="btn commonB" value="Comentar">
                @else
                    <button id="bc2" class="btn commonB">No puedes comentar hasta comprar</button>
                @endif
                
            @endif
    </form>
            <!-- 
            th:field="" -->
            <br>
            <br>
            <br>
            <br>
        
            <h2>Comentarios</h2>
            <div class="comentario row" >
            @foreach($comments as $comments)
                <div class="us_img" >
                    <a href="" ><b>{{$comments->name}}</b></a>
                    <div class="imgcomment">
                        <a><img src="data:image/jpeg;base64, {{$comments->user_avatar}}"  alt="100%x280" data-holder-rendered="true"></a>
                    </div>
                </div>
                <div class="u_commen">
                    <p>{{$comments->comment_content}}</p>
                </div>
                <div>
                    <p>{{$comments->created_at}}</p>
                </div>
                @endforeach
            </div>
<!--th:src="@{'/Imagen1/'+${allcomens.idUser}}"-->
        </div>
        
    

    <script>

    </script>

</body>
</html>