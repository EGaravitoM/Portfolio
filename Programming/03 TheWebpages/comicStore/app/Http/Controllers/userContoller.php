<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Hash;
use DB;
use Illuminate\Support\Facades\Auth;
use App\User;

class userContoller extends Controller
{
    public function create(Request $user){
        
        if($user->hasFile('imagenAvatar')){
            $file = $user->file('imagenAvatar')->getRealPath();
            $img = file_get_contents($file);
            $base64 = base64_encode($img);
        }
        $pass = Hash::make($user->password_user);
        DB::select('call generalUsuario(?,?,?,?,?,?,?,?,?,?,?)', Array(
            1,
            null,
            $user->name_user,
            $user->last_name,
            $user->email,
            $user->name,
            $pass,
            $base64,
            $user->address,
            $user->phone,
            0
        ));
        return redirect('/');

    }

    public function get($id){

    }

    public function getAll(){

    }

    public function delete($id){

    }

    public function update(Request $user){

    }

    public function login(Request $request){

        $credentials = $request->only('name', 'password');
            if (Auth::attempt($credentials)) {
                return redirect('/');
            }
            else{
                return redirect('/sing_in')->withErrors(['Las credenciales no coinciden', 'Las credenciales no coinciden']);;
            }

        $pass = Hash::make($request->password);
        return $pass;
        $query = new User();
        $usuario = $query->hydrate(
            DB::select(
                "call generalUsuario( 
                6,
                null,
                null,
                null,
                '$request->name',
                '$request->name',
                '$pass',
                null,
                null,
                null,
                null)"
            )
        ); 
        return $usuario;
        if($usuario!=""){
            $credentials = ['name'=>$request->name, 'password'=>$request->password];
            if (Auth::attempt($credentials)) {
                return redirect('/');
            }
            else{
                return redirect('/sing_in')->withErrors(['Las credenciales no coinciden', 'Las credenciales no coinciden']);;
            }
    
        }
    }

    public function logout()
    {
        Auth::logout();
        return redirect(url()->previous());
    }
}
