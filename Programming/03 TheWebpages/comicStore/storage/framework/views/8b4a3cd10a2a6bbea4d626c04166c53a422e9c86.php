<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Carrito</title>

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>

    <link rel="stylesheet" href="../css/reset.css">
    <link rel="stylesheet" href="../css/navbar.css">
    <link rel="stylesheet" href="../css/addart.css">

  </head>

  <body class="bg-light">

      <ul class="GNB fixed-top">
          <li class="GNB_E inicionav"></li>
          <li class="GNB_E"><a class="" href="/"><img class="logo" src="https://bit.ly/2u7pIbu"></a></li>
          <li class="GNB_E"><a class="GNB_A" href="/">Inicio</a></li>
          <?php if(Auth::user()): ?>
          <?php if(Auth::user()->rol == 1): ?>
          <li class="GNB_E"><a class="GNB_A" href="/articulo">Crear Comic</a></li>
          <?php endif; ?>
          <?php endif; ?>
          <li class="GNB_E"><a class="GNB_A" href="/buscar">Buscar</a></li>
          <li class="GNB_E SI finnav"></li>

          <?php if(Auth::guest()): ?>
          <li class="GNB_E SI"><a class="GNB_A" href="/sing_in">Ingresar</a></li>
          <?php else: ?>
          <li class="GNB_E SI"><a class="GNB_A" href="/logout" >Salir</a></li>
          <li class="GNB_E SI"><a class="GNB_A" href="/profile/<?php echo e(Auth::user()->id); ?>" ><?php echo e(Auth::user()->name); ?></a></li>
          <li class="GNB_E SI"><img id="uimg"  src="data:image/jpeg;base64, <?php echo e(Auth::user()->user_avatar); ?>" alt=""></li>
      
            <li class="GNB_E SI"><a class="GNB_A" href="/loadCart/<?php echo e(Auth::user()->id); ?>">Carrito</a></li>
         
          <?php endif; ?>
    </ul>

      <br>

    <div class="container">
      <div class="py-5 text-center">
        <img class="d-block mx-auto mb-4" src="https://getbootstrap.com/assets/brand/bootstrap-solid.svg" alt="" width="72" height="72">
        <h2>Checkout</h2>
        <p class="lead">This are all the items you have added to your cart.</p>
      </div>

      <div class="row">
        <div class="col-md-4 order-md-2 mb-4">
          <h4 class="d-flex justify-content-between align-items-center mb-3">
            <span class="text-muted">Your cart</span>
          </h4>
          
         
              <input type="hidden" name="allArts" value="$cart">
            <div style="background-color: aliceblue" >
              <table id="mytable" class="table table-bordred table-striped">
                
                <thead>
                  <th class="standard" >Nombre</th>
                  <th class="standard" >Unidades</th>
                  <th class="standard" >Precio</th>
                  <th class="standard" >Discutir</th> 
                  <th class="standard" >Comprar</th>
                  <th class="standard" >Eliminar</th> 
                </thead>
                <?php $__currentLoopData = $cart; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $cart): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
                <form action="/individualBuy" method="post">
                <?php echo csrf_field(); ?>

                <input type="hidden" name="radVal" class="radValHolder" value="">
                <input type="hidden" name="cart_id" value="<?php echo e($cart->id); ?>">
                  
                <tbody>
                  <td>
                    <div>
                      <h6 class="my-0" value="" ><?php echo e($cart->name_article); ?></h6>
                    </div>
                  </td>
                  <td>
                    <input type="number" name="newUnits" id="" min="1" max="<?php echo e($cart->ua); ?>" value="<?php echo e($cart->units); ?>">
                  </td>
                  <td>
                    <span class="text-muted" >$<?php echo e($cart->price); ?></span> 
                  </td>
                  <td>
                    <a name="Save" class="delfromcart" href="/loadDiscuss/<?php echo e($cart->id); ?>">Discutir<a>
                  </td>
                  <?php if($cart->price > 0): ?>
                  <td>
                    <input type="submit" class="btn btn-primary btn-block" Value="comprar">
                  </td>
                  <?php else: ?> 
                  <td>
                    <a name="Save" class="delfromcart" id="noPrecio">Comprar<a>
                  </td>
                  <?php endif; ?>
                  <td>
                    <a name="Save" class="delfromcart" href="/delCart/<?php echo e($cart->id); ?>">X<a>
                  </td>
                </tbody>
                </form>
                  <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
                
              </div>
              </table>
             
              <!--<div class="d-block my-3">
                <div class="custom-control custom-radio">
                  <input id="credit" name="paymentMethod" value="credit" type="radio" class="custom-control-input myRads" checked required>
                  <label class="custom-control-label" for="credit">Credit card</label>
                </div>
                <div class="custom-control custom-radio">
                  <input id="debit" name="paymentMethod" value="debit" type="radio" class="custom-control-input myRads" required>
                  <label class="custom-control-label" for="debit">Debit card</label>
                </div>
                <div class="custom-control custom-radio">
                  <input id="paypal" name="paymentMethod" value="paypal" type="radio" class="custom-control-input myRads" required>
                  <label class="custom-control-label" for="paypal">Paypal</label>
                </div>
              </div>-->
              <select name="payMent" id="methodsToPay" onchange="">
                <option disabled selected>Choose Payment Method</option>
                <option value="1">Credit</option>
                <option value="2">Debit</option>
                <option value="3">Paypal</option>
              </select>
              
              <form action="/buyAll" mehtod="post">
                <hr class="mb-4">
                <div id="pay"><button name="Save" value="Pay" class="btn btn-primary btn-block" type="submit">Pay</button></div>
                <div id="return"><a href="/"><button class="btn btn-block" type="button">Cancel</button></a></div>
                <input type="hidden" name="radholder" class="radValHolder">
              </form>
              
          
            
         
        </div>
        <div class="col-md-8 order-md-1">
          <form th:action="@{/cartAcc}" th:object="${carro}" method="post">

            <h4 class="mb-3">Payment</h4>

            
            <br><br><br><br><br><br><br><br>
           
          </form>
        </div>
      </div>

      
    </div>

   
    <script>

      $(document).ready(function(){
          $("#methodsToPay").change(function (){
            $(".radValHolder").val($(this).children("option:selected").val());
          })
            
      });
     
    </script>
  </body>
</html><?php /**PATH D:\LMAD\Septimo\BDM\PF\comicStore\resources\views/cart.blade.php ENDPATH**/ ?>