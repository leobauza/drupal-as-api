<nav class="site__menu">
  <ul>
    {{#each menu}}
      {{#unless this.depth}}
        <li class="{{#if @first}}first {{/if}}item{{#if @last}} last{{/if}}">
          <a data-nid='{{this.nid}}' href="{{this.path}}">{{this.title}}</a>
          {{#if this.below}}
            <ul>
              {{> list-item}}
            </ul>
          {{/if}}
        </li>
      {{/unless}}
    {{/each}}
  </ul>
</nav>
