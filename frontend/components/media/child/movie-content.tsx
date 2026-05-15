"use client";

import { Movie } from "@/lib/api";
import { motion } from "motion/react";
import { GenresList } from "./genres-list";
import { cn } from "@/lib/utils";

type Props = {
    movie: Movie,
    expanded: boolean,
}

export function MovieContent({ movie, expanded }: Props) {
    return (
        <div className="min-w-0 flex-1 p-4">
            <h2 className={cn("font-bold truncate", expanded ? "text-5xl" : "text-base")}>
                {movie.title}
            </h2>

            <p className={cn("text-sm text-muted-foreground", expanded ? "text-lg" : "text-sm")}>
                {movie.director}
            </p>
            
            <GenresList genres={movie.genres} mediaId={movie.id} />

            {expanded && (

                <motion.div
                    initial={{
                        opacity: 0,
                        y: 10,
                    }}

                    animate={{
                        opacity: 1,
                        y: 0,
                    }}

                    transition={{
                        delay: 0.2,
                    }}
                >

                    <p className="mt-4 text-sm leading-relaxed">
                        {movie.description}
                    </p>

                    <p className="mt-4 text-sm leading-relaxed">
                        {movie.duration_minutes} minutes
                    </p>
                </motion.div>
            )}

        </div>
    );
}