<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Comic Paradise</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>

    <link rel="stylesheet" href="../css/reset.css">

    <link rel="stylesheet" href="../css/indexstyle.css">
    

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
          <li class="GNB_E"><input class="GNB_S form-control" name="search" type="text" id="search" placeholder="Buscar">
          </li>
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
        
        <script>
            $(document).ready(function(){
              $("#search").on("keyup", function() {
                var value = $(this).val().toLowerCase();
                $(".eaf").filter(function() {
                  $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1);
                });
              });
              $(".cats").click( function() {
                var value = $(this).text().toLowerCase();
                console.log(value);
                $(".eaf").filter(function() {
                  $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1);
                });
              });
            });
        
        </script>
<br><br>
        <div style="width: 80%; margin-left:8em;">
            @foreach($cat as $cat)
              <small class="cats btn" value="{{$cat->name_category}}" >{{$cat->name_category}}</small>
            @endforeach
        </div>

        <div class="fistA album text-muted">
          <div class="objCont">
            <div class="infoProducto">
            @foreach($articles as  $articles)
              <div class="card eaf" value="{{$articles->name_article}} {{$articles->price}} {{$articles->description_article}}
                       {{$articles->name_category}} {{$articles->rating}} {{$articles->username}} {{$articles->created_at}}">
                <a class="" href="/product/{{$articles->id}}"><img class="art_img" alt="100%x280" src="data:image/jpeg;base64, {{$articles->img1}}" data-holder-rendered="true"></a>
                <div class="card-body">
                  <h5 class="card-title">
                    <a class="standard nphl" href="/product/{{$articles->id}}">{{$articles->name_article}}</a>
                  </h5>
                  <h6 class="">${{$articles->price}}</h6>
                  <small class="">{{$articles->name_category}}</small>
                  <small class="">★{{$articles->rating}}</small><br>
                  <small class="">Unidades: {{$articles->units}}</small><br>
                  <small class="">Creado: {{$articles->created_at}}</small>
                  <i class="fas fa-star"></i>
                </div>
              </div>
              @endforeach
            </div>
          </div>
        </div>
        

           
               


        
        


    
   

</body>
</html>