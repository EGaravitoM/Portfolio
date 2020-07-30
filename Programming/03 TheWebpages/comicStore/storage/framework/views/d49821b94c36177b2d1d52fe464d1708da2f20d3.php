<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Registro</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>


    <link rel="stylesheet" href="../css/singup.css">
    <link rel="stylesheet" href="../css/reset.css">

</head>
<body style="padding-left: 5%; padding-top: 50px">

    <div class="container">
        
        <form action="/registro" method="post" enctype="multipart/form-data">
                <?php echo csrf_field(); ?>
                <input type="hidden" id="id">

                <div class="form-group">
                    <label for="personname">Nombre</label>
                    <input type="text" class="form-control" id="personname" placeholder="Nombre" name="name_user" required />
                    <small id="personnameHelp" class="form-text text-muted">Tu Nombre</small>
                </div>

                <div class="form-group">
                    <label for="lastname">Apellido</label>
                    <input type="text" class="form-control" id="lastname" placeholder="Apellido" name="last_name" required>
                    <small id="lastnameHelp" class="form-text text-muted">Tu Apellido.</small>
                </div>

                <div class="form-group">
                    <label for="correoe">Email</label>
                    <input type="email" class="form-control" id="correoe" name="email" aria-describedby="emailHelp" placeholder="Email"  required>
                    <small id="emailHelp" class="form-text text-muted">Ingresa tu correo electrónico</small>
                </div>

                <div class="form-group">
                    <label for="nusuario">Nombre de Ususario</label>
                    <input type="text" class="form-control" id="nusuario" placeholder="Nombre de Ususario" name="name" required>
                    <small id="usernameHelp" class="form-text text-muted">Elija un Nombre de Ususario.</small>
                </div>

                <div class="form-group">
                  <label for="contraseña">Contraseña</label>
                  <input type="password" class="form-control" id="contraseña" placeholder="Contraseña" name="password_user" required>
                  <small id="passwordHelp" class="form-text text-muted">Recomendamos el uso de mayúsculas, minúsculas y numeros.</small>
                </div>

                <div class="form-group">
                    <label for="telusuario">Telefono</label>
                    <input type="text" class="form-control" id="telusuario" placeholder="Telefono" name="phone">
                    <small id="telHelp" class="form-text text-muted">Ingrese su numero de celular.</small>
                </div>

                <div class="form-group">
                    <label for="dirusuario">Direccion</label>
                    <input type="text" class="form-control" id="dirusuario" placeholder="Direccion" name="address">
                    <small id="dirHelp" class="form-text text-muted">Ingrese su direccion.</small>
                </div>

                <div class="form-group">
                    <label for="pp">Elija una foto de perfil</label><br>
                    <input type="file" name="imagenAvatar" id="pp" required>
                    <small id="ppHelp" class="form-text text-muted">Puede ser cambiada despues</small>
                </div>

                <button id="go" type="submit" class="btn commonB" style="float: right;">Registrar</button>
                <button id="nogo" type="reset" class="btn commonB" style="float: left;">Cancelar</button>

                </div>

                
              </form>

</div>


    <script>
        $("#nogo").click(function(){
            window.location.href = "/";
        });
        
        $("#go").click(function(){
            var pass = $("#contraseña").value();
            var  caps = false, minus = false, num = false;
            if ($("#nusuario").length <= 5) {
                alert("El nombre de ususario debe de ser de 6 caracteres o más :v");
            }

            if($("#contraseña").length <= 7) {
                alert("La contraseña debe ser de 8 caracteres o más :v");
            }

            for (let i = 0; i < $("#contraseña").length; i++) {

                if(isNaN(pass.charAt(i))){

                    if(pass.charAt(i) == toUpperCase(pass.charAt(i))){
                        caps = true;
                    }  

                    if(pass.charAt(i) == toLowerCase(pass.charAt(i))){
                        minus = true;
                    } 

                }
                else{
                    num = true;
                }  
            }

            if(caps && minus && num){
                alert("La contraseña debe una Mayuscula, Minúscula y Número :v");
            }

        });
        
        

    </script>

</body>
</html><?php /**PATH D:\LMAD\Septimo\BDM\PF\comicStore\resources\views/sing_up.blade.php ENDPATH**/ ?>