Rails.application.routes.draw do
  get 'accounts/new'

  get 'accounts/show'

  get 'accounts/edit'

  # static pages
  root to: 'static#root'
  get '/contact', to: 'static#contact'

  # user pages
  get '/signup', to: 'users#new'
  post '/signup', to: 'users#create'

  # sessions pages
  get '/login', to: 'sessions#new'
  post '/login', to: 'sessions#create'
  delete '/login', to: 'sessions#delete'

  # account pages
  post '/accounts/new', to: 'accounts#create'
  

  # exclude index page for user and account resources
  resources :users, only: [:new, :show, :edit, :create, :destroy, :update]
  resources :accounts, only: [:new, :show, :edit, :create, :destroy, :update]
end
