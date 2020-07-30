<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Perfil</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">


    <link rel="stylesheet" type="text/css" media="screen" href="../css/profile.css" />
    <link rel="stylesheet" type="text/css" media="screen" href="../css/reset.css" />
    <link rel="stylesheet" href="../css/navbar.css">

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

    <br><br>

  <br>
    <div class="col-md-5  toppad  pull-right col-md-offset-3 ">
    @if(Auth::guest())

    @else
      @if (Auth::user()->id == $viewdUser->id)
          <!--<a class="commonB btn" href="edit.html" >Editar Perfil</a> -->
      @endif
    @endif
        <br>
         <!--<p class="standard">May 05,2014,03:00 pm </p> -->
    </div>
    <div class="col-xs-12 col-sm-12 col-md-6 col-lg-6 col-xs-offset-0 col-sm-offset-0 col-md-offset-3 col-lg-offset-3 toppad mainbox" >

            <div class="panel panel-info">
              <div class="panel-heading">
                <h3 class="small-title panel-title uNameTitle">{{$viewdUser->name}}</h3>
              </div>
              <div class="panel-body">
                <div class="row">
                  <div class="col-md-3 col-lg-3 fotouser"> <img alt="User Pic" src="data:image/jpeg;base64, {{$viewdUser->user_avatar}}" class="imgfotouser"> </div>
                  
                  <div class=" col-md-9 col-lg-9 "> 
                    <table class="table table-user-information">
                      <tbody>
                        <tr>
                          <td>Nombre:</td>
                          <td>{{$viewdUser->name_user}} {{$viewdUser->last_name}}</td>
                        </tr>
                        <tr>
                          <td>Correo</td>
                          <td><a class="correo" href="mailto:info@support.com">{{$viewdUser->email}}</a></td>
                        </tr>
                        <tr>
                          <td>Telefono:</td>
                          <td>{{$viewdUser->phone}}</td>
                        </tr>
                        <tr>
                          <td>Dirección:</td>
                          <td>{{$viewdUser->address}}</td>
                        </tr>
                      </tbody>
                    </table>
                  </div>
                </div>
              </div>
              
            </div>

            

    </div>

    <div class="container">
        <div class="row">
            
            
            <div class="col-md-12">
            <div class="clearfix "></div>

            @if (Auth::guest() || Auth::user()->id != $viewdUser->id)
              <h4  class="small-title">Creaciones</h4>
              <div class="table-responsive">
                    <table id="mytable" class="table table-bordred table-striped">
                      <thead>
                        <th class="standard" >Nombre</th>
                        <th class="standard" >Rating</th>
                        <th class="standard" >Precio</th>
                        <th class="standard" >Unidades</th> 
                      </thead>
                      <tbody>
                      @foreach ($myComics as $myComics)
                      <tr>
                        <td><a href="/product/{{$myComics->id}}" class="standard" >{{$myComics->name_article}}</a></td>
                        <td>{{$rating->rating}}</td>
                        <td>${{$myComics->price}}</td>
                        <td>{{$myComics->units}}</td>
                      </tr>
                      @endforeach
                    </tbody>
                  </table>
      
              <div class="clearfix "></div>
            @else
            <h4  class="small-title">Creaciones</h4>
            <div class="table-responsive">
                  <table id="mytable" class="table table-bordred table-striped">
                    <thead>
                      <th class="standard" >Nombre</th>
                      <th class="standard" >Rating</th>
                      <th class="standard" >Precio</th>
                      <th class="standard" >Unidades</th>
                      <th class="standard" >Habilitado</th>
                      <th class="standard" >Editar</th>
                      <th class="standard" >Eliminar</th>
                    </thead>
                    <tbody>
                    @foreach ($myComics as $myComics)
                    <tr>
                      <td><a href="/product/{{$myComics->id}}" class="standard" >{{$myComics->name_article}}</a></td>
                      <td>{{$rating->rating}}</td>
                      <td>${{$myComics->price}}</td>
                      <td>{{$myComics->units}}</td>
                      <td>
                        <a href="/activate/{{$myComics->id}}/{{$myComics->active_article}}">
                          @if($myComics->active_article == '1')
                                  Sí
                                @else
                                  No
                                @endif
                        </a>
                      </td>
                      <td><a href="/editArticle/{{$myComics->id}}">Editar</a></td>
                      <td><a href="/deleteArticle/{{$myComics->id}}">Eliminar</a></td>
                    </tr>
                    @endforeach
                  </tbody>
                </table>
                  <br><br><br>
                <h4  class="small-title">Compras</h4>
            <div class="table-responsive">
                  <table id="mytable" class="table table-bordred table-striped">
                    <thead>
                      <th class="standard" >Nombre</th>
                      <th class="standard" >Rating</th>
                      <th class="standard" >Precio</th>
                      <th class="standard" >Unidades</th>
                    </thead>
                    <tbody>
                    @foreach ($myBuys as $myBuys)
                    <tr>
                      <td><a href="/product/{{$myBuys->article_id}}" class="standard" >{{$myBuys->name_article}}</a></td>
                      <td>{{$rating->rating}}</td>
                      <td>${{$myBuys->total}}</td>
                      <td>{{$myBuys->units_cart}}</td>
                    </tr>
                    @endforeach
                  </tbody>
                </table>
    
            <div class="clearfix "></div>
            @endif
    <div>
        <a href="/" class="btn commonB" id="yoQuieroIrACasa">Inicio</a>
    </div>
   
    </div>

    
        
    </div>
    </div>
    </div>
</div>

<br><br><br><br><br><br>

</body>
</html>