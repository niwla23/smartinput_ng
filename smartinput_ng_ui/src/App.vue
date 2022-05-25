<script setup lang="ts">
import Home from "./Home.vue";
</script>

<template>
  <Suspense>
    <template #fallback>
      <div>loading</div>
    </template>

    <Home />
  </Suspense>
</template>

