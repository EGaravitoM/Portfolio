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


    <form method="post" action="/generateDiscution">
        @csrf
        <div class="container form-group comentgroup">
                <textarea placeholder="Añade un comentario..." name="discuss" id="cbox" cols="150" rows="3" required></textarea>
                <input type="submit" id="bc2" class="btn commonB" value="Comentar">
                <input type="hidden" value="{{Auth::user()->id}}" name="user_id">
                <input type="hidden" value="{{$idcart}}" name="cart_id">
                <input type="hidden" value="{{$idarticle}}" name="article_id">
        </form>
    @if(Auth::user()->rol == 1)
    <form method="post" action="/setPrice">
    @csrf
        <input type="number" class="form-control" style="width: 7.7em;" name="fPrice" id="" required>
        <input type="submit" class="btn commonB" value="Asignar Precio">
        <input type="hidden" value="{{$idcart}}" name="cart_id">
    </form>
    @endif
            <br>
            <br>
            <br>
            <br>
        
            <h2>Comentarios</h2>
            <div class="comentario row" >
                @foreach($dis as $dis)
                <div class="us_img" >
                    <a href="" ><b>{{$dis->name}}</b></a>
                </div>
                <div class="u_commen">
                    <p>{{$dis->discussion_content}}</p>
                </div>
                <div>
                    <p>{{$dis->created_at}}</p>
                </div>
                @endforeach
            </div>
<!--th:src="@{'/Imagen1/'+${allcomens.idUser}}"-->
        </div>
        
    

    <script>

    </script>

</body>
</html>